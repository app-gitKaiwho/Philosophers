/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:54:56 by lvon-war          #+#    #+#             */
/*   Updated: 2023/09/04 16:46:00 by lvon-war         ###   ########.fr       */
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

int error_manager(int err_code, char * err_msg);
int	ft_atoi(const char *str);

typedef struct philobot
{
	pthread_mutex_t	fourchette;
	pthread_t		thread;
	struct timeval	lastmeal;
	int				id;
	int				Nate;
}t_philobot;

typedef struct data
{
	t_philobot		*philobots;
    struct timeval	global;
	int				number_of_philobot;
	int				must_eat_n_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}t_data;

#endif /*!PHILO_H */