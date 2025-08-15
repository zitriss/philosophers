/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:13:26 by tlize             #+#    #+#             */
/*   Updated: 2025/08/15 17:11:50 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
            pthread_mutex_lock(&data->death_mutex);
            if (current_time_ms() - philos[i].last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->print_mutex);
                printf("Philosophe %d est mort\n", philos[i].id);
                pthread_mutex_unlock(&data->print_mutex);

                data->someone_died = 1;
                pthread_mutex_unlock(&data->death_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->death_mutex);
            i++;
        }

        pthread_mutex_lock(&data->death_mutex);
        if (data->someone_died)
        {
            pthread_mutex_unlock(&data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&data->death_mutex);

        usleep(1000); // éviter un busy loop
    }
    return NULL;
}
