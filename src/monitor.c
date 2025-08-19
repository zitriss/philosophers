/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:13:26 by tlize             #+#    #+#             */
/*   Updated: 2025/08/19 16:42:48 by tlize            ###   ########.fr       */
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

static int	check_death(t_philo philo, t_data *data)
{
	int	i;

	i = 0;
	if (current_time_ms() - philo.last_meal > data->time_to_die
		&& !is_simulation_ended(data))
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%d died\n", philo.id);
		pthread_mutex_unlock(&data->print_mutex);
		set_simulation_ended(data);
		i = 1;
	}
	return (i);
}

static int	check_belly(t_data *data, int has_eaten)
{
	int	i;

	i = 0;
	if (has_eaten >= data->nb_philo)
	{
		set_simulation_ended(data);
		i = 1;
	}
	return (i);
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
			if (check_death(philos[i], data))
				return (NULL);
			i++;
			if (data->nb_meals > 0 && philos[i].meals_eaten >= data->nb_meals)
				has_eaten ++;
		}
		if (check_belly(data, has_eaten))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
