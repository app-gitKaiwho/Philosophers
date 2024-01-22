/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:54:56 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 14:11:57 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "stddef.h"
# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include "sys/time.h"

typedef struct data
{
	struct timeval	global;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
	long			expiration_time;
	long			sleep_time;
	long			eat_time;
	int				min_eat;
	int				philo_n;
	int				f_eat;
	int				flag_dead;
}t_data;

typedef struct philobot	t_philobot;

struct philobot
{
	struct timeval	last_meal;
	pthread_mutex_t	pdata;
	pthread_mutex_t	fork;
	t_data			*data;
	t_philobot		*next;
	int				id;
	int				fork_locked;
	int				finished;
}t;

//utils
long	whatttime(pthread_mutex_t *mutex, struct timeval global);
int		check_free_fork(t_philobot *philo);
int		check_death(t_philobot *philo);
int		is_finished(t_philobot *philobot);

//minilib
int		ft_atoi(const char *str);
int		ft_wdcount(char **str);

//philoaction
void	good_sleep(t_philobot *philo);
void	eat(t_philobot *philo, int *ate_n);

//atomicfunc
void	atomic_print(t_data *data, char *txt, int id);
void	atomic_actualise_time(t_philobot *philo);
void	atomic_set_data(pthread_mutex_t	*mutex, int *data, int val);
int		atomic_fetch_data(pthread_mutex_t	*mutex, int *data);

#endif /*!PHILO_H */