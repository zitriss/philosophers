/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:13:26 by tlize             #+#    #+#             */
/*   Updated: 2025/08/17 15:31:36 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int is_simulation_ended(t_data *data)
{
    int ended;

    pthread_mutex_lock(&data->simulation_mutex);
    ended = data->simulation_ended;
    pthread_mutex_unlock(&data->simulation_mutex);
    return (ended);
}

void set_simulation_ended(t_data *data)
{
    pthread_mutex_lock(&data->simulation_mutex);
    data->simulation_ended = 1;
    pthread_mutex_unlock(&data->simulation_mutex);
}

void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    t_data *data = philos[0].data;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->nb_philo)
        {
            if (current_time_ms() - philos[i].last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->print_mutex);
                printf("Philosophe %d est mort\n", philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);

                set_simulation_ended(data);
                return NULL;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}
