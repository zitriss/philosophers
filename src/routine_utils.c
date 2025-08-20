/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:35:09 by tlize             #+#    #+#             */
/*   Updated: 2025/08/20 18:39:24 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	eat_left(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(philo->left_fork);
		return ;		
	}
	printf("%ld %d has taken a fork\n", timer(data), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;		
	}
	printf("%ld %d has taken a fork\n", timer(data), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&philo->lmeal);
	philo->last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->lmeal);
	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%ld %d is eating\n", timer(data), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&philo->emeal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->emeal);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat_right(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%ld %d has taken a fork\n", timer(data), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%ld %d has taken a fork\n", timer(data), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&philo->lmeal);
	philo->last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->lmeal);
	pthread_mutex_lock(&data->print_mutex);
	if (is_simulation_ended(data))
	{
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	printf("%ld %d is eating\n", timer(data), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(&philo->emeal);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->emeal);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
