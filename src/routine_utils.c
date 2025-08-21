/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:35:09 by tlize             #+#    #+#             */
/*   Updated: 2025/08/21 08:15:48 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_simulation_ended(philo->data))
		printf("%ld %d %s\n", timer(philo->data), philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

static void	eat_norm(t_philo *philo, t_data *data)
{
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->emeal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->emeal);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat_left(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	safe_print(philo, "has taken a fork");
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->lmeal);
	philo->last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->lmeal);
	eat_norm(philo, data);
}

void	eat_right(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->right_fork);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	safe_print(philo, "has taken a fork");
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->lmeal);
	philo->last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->lmeal);
	eat_norm(philo, data);
}
