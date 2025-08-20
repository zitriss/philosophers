/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:16:16 by tlize             #+#    #+#             */
/*   Updated: 2025/08/20 17:19:56 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int 		i;
	t_data		data;
	t_philo		*philos;
	pthread_t	*threads;
	pthread_t	monitor_thread;
	
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [nb_meals]\n");
		return (1);
	}
	if (init_data(&data, argc, argv))
		return (printf("Erreur d'initialisation data\n"), 1);
	if (init_philosophers(&data, &philos))
		return (printf("Erreur d'initialisation philosophes\n"), 1);
	threads = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!threads)
		return (printf("Erreur malloc threads\n"), 1);
	for (i = 0; i < data.nb_philo; i++)
		pthread_create(&threads[i], NULL, philo_routine, &philos[i]);
	pthread_create(&monitor_thread, NULL, monitor_routine, philos);
	pthread_join(monitor_thread, NULL);
    for (i = 0; i < data.nb_philo; i++)
		pthread_join(threads[i], NULL);
	free(threads);
	free(philos);
	free(data.forks);
	pthread_mutex_destroy(&data.simulation_mutex);
	return (0);
}

