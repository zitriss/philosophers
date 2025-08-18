/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:35:09 by tlize             #+#    #+#             */
/*   Updated: 2025/08/18 18:41:05 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	precise_sleep(long duration_ms)
{
	long	start;

	start = current_time_ms();
	while (current_time_ms() - start < duration_ms)
		usleep(100);
}

void	eat_left(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d has taken a fork\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d has taken a fork\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	philo->last_meal = current_time_ms();
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d is eating\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	philo->meals_eaten++;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat_left(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d has taken a fork\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d has taken a fork\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	philo->last_meal = current_time_ms();
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d is eating\n", current_time_ms(), philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	philo->meals_eaten++;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
