/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:13:26 by tlize             #+#    #+#             */
/*   Updated: 2025/08/21 07:34:55 by tlize            ###   ########.fr       */
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

static int check_death(t_philo *philo, t_data *data)
{
    pthread_mutex_lock(&philo->lmeal);
    if (current_time_ms() - philo->last_meal > data->time_to_die
        && !is_simulation_ended(data))
    {
        pthread_mutex_unlock(&philo->lmeal);
        pthread_mutex_lock(&data->print_mutex);
        printf("%ld %d died\n", timer(data), philo->id);
        pthread_mutex_unlock(&data->print_mutex);
        set_simulation_ended(data);
        return (1);
    }
	else
    	pthread_mutex_unlock(&philo->lmeal);
    return (0);
}

static int	check_belly(t_data *data, t_philo *philos)
{
	int	i;
	int has_eaten;

	i = 0;
	has_eaten = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philos[i].emeal);
		if (philos[i].meals_eaten >= data->nb_meals)
			has_eaten++;
		pthread_mutex_unlock(&philos[i].emeal);
		i++;
	}
	if (has_eaten == data->nb_philo)
	{
		set_simulation_ended(data);
		return(1);
	}
	return (0);
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
	while (!is_simulation_ended(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(philos, data))
				return (NULL);
			i++;
		}
		if (data->nb_meals> 0 && check_belly(data, philos))
		{
			
			return (NULL);			
		}
		usleep(1000);
	}
	return (NULL);
}
