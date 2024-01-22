/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomicfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:01 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 19:21:02 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	atomic_print(t_data *data, char *txt, int id)
{
	pthread_mutex_lock(&data->print_mutex);
	if (id < 0)
		printf("%ldms %s\n", whatttime(&data->data_mutex, data->global), txt);
	else
		printf("%ldms %d %s\n", whatttime(&data->data_mutex, data->global),
			id, txt);
	pthread_mutex_unlock(&data->print_mutex);
}

void	atomic_actualise_time(t_philobot *philo)
{
	pthread_mutex_lock(&philo->pdata);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->pdata);
}

void	atomic_set_data(pthread_mutex_t *mutex, int *data, int val)
{
	pthread_mutex_lock(mutex);
	*data = val;
	pthread_mutex_unlock(mutex);
}

int	fetch_data(pthread_mutex_t *mutex, int *data)
{
	int	tmp;

	pthread_mutex_lock(mutex);
	tmp = *data;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

long	whatttime(pthread_mutex_t *mutex, struct timeval global)
{
	struct timeval	now;
	int				val;	

	pthread_mutex_lock(mutex);
	gettimeofday(&now, NULL);
	val = ((now.tv_sec - global.tv_sec) * 1000
			+ (now.tv_usec - global.tv_usec) / 1000);
	pthread_mutex_unlock(mutex);
	return (val);
}
