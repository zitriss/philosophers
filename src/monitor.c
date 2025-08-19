/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:13:26 by tlize             #+#    #+#             */
/*   Updated: 2025/08/19 14:52:24 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_simulation_ended(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->simulation_mutex);
	ended = data->simulation_ended;
	pthread_mutex_unlock(&data->simulation_mutex);
	return (ended);
}

void	set_simulation_ended(t_data *data)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->simulation_ended = 1;
	pthread_mutex_unlock(&data->simulation_mutex);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;
	int		has_eaten;

	has_eaten = 0;
	philos = (t_philo *)arg;
	data = philos[0].data;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (current_time_ms() - philos[i].last_meal > data->time_to_die
				&& !is_simulation_ended(data))
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("Philosophe %d est mort\n", philos[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				set_simulation_ended(data);
				return (NULL);
			}
			i++;
			if (data->nb_meals > 0 && philos[i].meals_eaten > data->nb_meals)
				has_eaten ++;
		}
		if (has_eaten == data->nb_philo)
		{
			set_simulation_ended(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
