/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:16:16 by tlize             #+#    #+#             */
/*   Updated: 2025/08/17 15:31:28 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philos;
    pthread_t *threads;
    pthread_t monitor_thread;
    int i;

    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [nb_meals]\n");
        return 1;
    }

    if (init_data(&data, argc, argv))
        return (printf("Erreur d'initialisation data\n"), 1);
    if (init_philosophers(&data, &philos))
        return (printf("Erreur d'initialisation philosophes\n"), 1);

    threads = malloc(sizeof(pthread_t) * data.nb_philo);
    if (!threads)
        return (printf("Erreur malloc threads\n"), 1);

    // Lancer tous les threads philosophe
    for (i = 0; i < data.nb_philo; i++)
        pthread_create(&threads[i], NULL, philo_routine, &philos[i]);

    // Lancer le monitor
    pthread_create(&monitor_thread, NULL, monitor_routine, philos);

    // Attendre la fin du monitor
    pthread_join(monitor_thread, NULL);

    // Après un décès, terminer tous les threads philos
    for (i = 0; i < data.nb_philo; i++)
        pthread_join(threads[i], NULL);

    free(threads);
    free(philos);
    free(data.forks);
    pthread_mutex_destroy(&data.simulation_mutex);
    return 0;
}

