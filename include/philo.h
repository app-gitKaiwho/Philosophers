/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:54:56 by lvon-war          #+#    #+#             */
/*   Updated: 2023/09/18 18:09:46 by lvon-war         ###   ########.fr       */
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
	pthread_t	thread;
}t_philobot;

typedef struct data
{
	t_philobot		*philobots;
	int				compteur;
	pthread_mutex_t	data;
}t_data;

int				error_manager(int err_code, char *err_msg);
//void			atomic_print(t_data *data, char *txt);
int				ft_atoi(const char *str);

#endif /*!PHILO_H */