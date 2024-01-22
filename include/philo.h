/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:54:56 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 23:30:50 by lvon-war         ###   ########.fr       */
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

typedef struct s_philobot	t_philobot;

struct s_philobot
{
	struct timeval	last_meal;
	pthread_mutex_t	pdata;
	pthread_mutex_t	fork;
	t_data			*data;
	t_philobot		*next;
	int				id;
	int				fork_locked;
	int				finished;
};

//pthread
void	*damocles(void *arg);
void	*philobot(void *arg);
void	process(pthread_t	*threads, t_philobot *philobots);

//utils
int		check_death(t_philobot *philo);
int		is_finished(t_philobot *philobot);
int		lock_mutex(t_philobot *philo);
void	unlock_mutex(t_philobot *philo);
void	free_all(t_philobot *philobot, pthread_t *threads);

//minilib
int		ft_atoi(const char *str);
int		ft_wdcount(char **str);

//philoaction
void	good_sleep(t_philobot *philo);
int		eat(t_philobot *philo, int *ate_n);

//damoclesaction
int		everyone_ate(t_philobot *philobots, t_data *data, int i);
int		someone_died(t_philobot *philobots, t_data *data, int i);

//atomicfunc
void	atomic_print(t_data *data, char *txt, int id);
void	atomic_actualise_time(t_philobot *philo);
void	atomic_set_data(pthread_mutex_t	*mutex, int *data, int val);
int		fetch_data(pthread_mutex_t	*mutex, int *data);
long	whatttime(pthread_mutex_t *mutex, struct timeval global);

#endif /*!PHILO_H */