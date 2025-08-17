/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:55:53 by tlize             #+#    #+#             */
/*   Updated: 2025/08/17 15:31:30 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

//structs

typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t	print_mutex;
	int				simulation_ended;
	pthread_mutex_t	simulation_mutex;
} t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
} t_philo;

typedef struct s_monitor_arg
{
    t_data *data;
    t_philo *philos;
} t_monitor_arg;

//init
int 		init_data(t_data *data, int argc, char **argv);
int			init_philosophers(t_data *data, t_philo **philos);

//routine
void 		*philo_routine(void *arg);
void 		*monitor_routine(void *arg);
int 		is_simulation_ended(t_data *data);
void		set_simulation_ended(t_data *data);

//utils
long		ft_atol(const char *str);
long long 	current_time_ms(void);
void 		precise_sleep(long duration_ms);
void		eat_left(t_philo *philo);
void		eat_right(t_philo *philo);

#endif