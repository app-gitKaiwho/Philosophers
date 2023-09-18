/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:54:56 by lvon-war          #+#    #+#             */
/*   Updated: 2023/09/12 18:08:29 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "stddef.h"
# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include <sys/time.h>

typedef struct philobot
{
	pthread_mutex_t	fourchette;
	pthread_t		thread;
	struct timeval	lastmeal;
	int				id;
	int				n_ate;
}t_philobot;

typedef struct data
{
	t_philobot		*philobots;
	struct timeval	global;
	int				number_of_philobot;
	int				must_eat_n_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
}t_data;

typedef struct folder
{
	t_data	data;
	int		id_philo;
	int		id_next;
}t_folder;

int				error_manager(int err_code, char *err_msg);
struct timeval	eat(t_data *data, int id, int id_next);
void			smallsleep(t_data *data, int id);
int				ft_atoi(const char *str);

#endif /*!PHILO_H */