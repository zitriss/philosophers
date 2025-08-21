/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:16:16 by tlize             #+#    #+#             */
/*   Updated: 2025/08/21 08:47:25 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_data *data, t_philo *philos, pthread_t *threads)
{
	free(threads);
	free(philos);
	free(data->forks);
	pthread_mutex_destroy(&data->simulation_mutex);
}

int	start_simulation(t_data *data, t_philo *philos, pthread_t **threads)
{
	int			i;
	pthread_t	monitor_thread;

	*threads = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!*threads)
		return (printf("Erreur malloc threads\n"), 1);
	i = -1;
	while (++i < data->nb_philo)
		pthread_create(&(*threads)[i], NULL, philo_routine, &philos[i]);
	pthread_create(&monitor_thread, NULL, monitor_routine, philos);
	pthread_join(monitor_thread, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join((*threads)[i], NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	*threads;

	if (!validate_arguments(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (printf("Erreur d'initialisation data\n"), 1);
	if (init_philosophers(&data, &philos))
		return (printf("Erreur d'initialisation philosophes\n"), 1);
	if (start_simulation(&data, philos, &threads))
		return (1);
	cleanup(&data, philos, threads);
	return (0);
}
