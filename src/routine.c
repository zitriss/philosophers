/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:05:36 by tlize             #+#    #+#             */
/*   Updated: 2025/08/21 07:59:49 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	timer(t_data *data)
{
	return (current_time_ms() - data->start_time);
}

static void	think(t_philo *philo)
{
	t_data	*data;
	long	think_time;

	data = philo->data;
	pthread_mutex_lock(&philo->lmeal);
	think_time = data->time_to_die
		- (current_time_ms() - philo->last_meal) - data->time_to_eat;
	pthread_mutex_unlock(&philo->lmeal);
	if (think_time < 0)
		think_time = 0;
	if (think_time > 50)
		think_time = 50;
	if (is_simulation_ended(data))
		return ;
	safe_print(philo, "is thinking");
	usleep(1000 * think_time);
}

static void	eat(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        safe_print(philo, "has taken a fork");
        usleep(philo->data->time_to_die * 1000 + 1000);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
	
	if (philo->id % 2 == 0)
		eat_right(philo);
	else
		eat_left(philo);
}

static void	sleep_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (is_simulation_ended(data))
		return ;
	safe_print(philo, "is sleeping");
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
		if (is_simulation_ended(data))
			return (NULL);
		sleep_philo(philo);
		if (is_simulation_ended(data))
			return (NULL);
		think(philo);
	}
	return (NULL);
}
