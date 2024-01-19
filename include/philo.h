/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:54:56 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/19 17:04:53 by lvon-war         ###   ########.fr       */
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
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	print_mutex;
	long			expiration_time;
	long			sleep_time;
	long			eat_time;
	int				min_eat;
	int				philo_n;
	int				flag_eat;
}t_data;

typedef struct philobot
{
	struct timeval	last_meal;
	pthread_mutex_t	philodatamutex;
	pthread_mutex_t	fork;
	pthread_t		thread;
	t_data			*data;
	void			*next;
	int				id;
	int				finished;
}t_philobot;

//utils
int		error_manager(int err_code, char *err_msg);
void	atomic_print(t_data *data, char *txt, int id);
long	whatttime(struct timeval global);
void	atomic_actualise_time(t_philobot *philo);

//minilib
int		ft_atoi(const char *str);
int		ft_wdcount(char **str);

//philoaction
void	good_sleep(t_philobot *philo);
void	eat(t_philobot *philo);
int		is_finished(t_philobot *philobot);
#endif /*!PHILO_H */