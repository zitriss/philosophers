/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:35:09 by tlize             #+#    #+#             */
/*   Updated: 2025/08/17 15:15:06 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long current_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void precise_sleep(long duration_ms)
{
    long start = current_time_ms();
    while (current_time_ms() - start < duration_ms)
        usleep(100); // pause de 0.1ms pour rester réactif
}

void eat_left(t_philo *philo)
{
    t_data *data = philo->data;

    //left fork
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&data->print_mutex);
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    //right fork
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&data->print_mutex);
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    //eat
    philo->last_meal = current_time_ms();
    pthread_mutex_lock(&data->print_mutex);
    printf("%d is eating\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    philo->meals_eaten++;
    usleep(data->time_to_eat * 1000);
    //unlock forks
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void eat_right(t_philo *philo)
{
    t_data *data = philo->data;

    //right fork
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&data->print_mutex);
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    //left fork
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&data->print_mutex);
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    //eat
    philo->last_meal = current_time_ms();
    pthread_mutex_lock(&data->print_mutex);
    printf("%d is eating\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    philo->meals_eaten++;
    usleep(data->time_to_eat * 1000);
    //unlock forks
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}