/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:05:36 by tlize             #+#    #+#             */
/*   Updated: 2025/08/19 16:43:10 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	think(t_philo *philo)
{
	t_data	*data;
	long	think_time;

	data = philo->data;
	think_time = data->time_to_die
		- (current_time_ms() - philo->last_meal) - data->time_to_eat;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 50)
		think_time = 50;
	pthread_mutex_lock(&data->print_mutex);
	if (!is_simulation_ended(data))
		printf("%lld %d is thinking\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	usleep(1000 * think_time);
}

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		eat_right(philo);
	else
		eat_left(philo);
}

static void	sleep_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print_mutex);
	if (!is_simulation_ended(data))
		printf("%lld %d is sleeping\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	usleep(data->time_to_sleep * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!is_simulation_ended(data))
	{
		eat(philo);
		if (!is_simulation_ended(data))
			sleep_philo(philo);
		if (!is_simulation_ended(data))
			think(philo);
	}
	return (NULL);
}
