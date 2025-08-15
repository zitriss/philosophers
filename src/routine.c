/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:05:36 by tlize             #+#    #+#             */
/*   Updated: 2025/08/15 18:02:22 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void think(t_philo *philo)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&data->print_mutex);
    printf("%d is thinking\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    usleep(1000);
}

static void eat(t_philo *philo)
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
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    philo->meals_eaten++;
    usleep(data->time_to_eat * 1000);
    //unlock forks
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

static void sleep_philo(t_philo *philo)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&data->print_mutex);
    printf("%d is sleeping\n", philo->id);
    pthread_mutex_unlock(&data->print_mutex);
    usleep(data->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;

    while (!data->someone_died &&
           (data->nb_meals == -1 || philo->meals_eaten < data->nb_meals))
    {
        think(philo);
        eat(philo);
        sleep_philo(philo);
    }
    return NULL;
}
