/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:29:40 by tlize             #+#    #+#             */
/*   Updated: 2025/08/11 21:45:47 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long ft_atol(const char *str)
{
	long res = 0;
	int i = 0;
	while(str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res);
}

int init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->nb_meals = ft_atol(argv[5]);
	else
		data->nb_meals = -1;
	data->someone_died = 0;
	if (data->nb_philo <= 0 || data->time_to_die <= 0
        || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
        return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks)
        return (1);
	for (int i = 0; i < data->nb_philo; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    pthread_mutex_init(&data->print_mutex, NULL);
    return (0);
}