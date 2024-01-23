/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomicfunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:20:01 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/23 16:55:39 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	atomic_print(t_data *data, char *txt, int id)
{
	if (fetch_data(&data->data_mutex, &data->flag_dead))
		return ;
	pthread_mutex_lock(&data->print_mutex);
	if (fetch_data(&data->data_mutex, &data->flag_dead))
	{
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
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
	long			val;

	pthread_mutex_lock(mutex);
	gettimeofday(&now, NULL);
	val = ((now.tv_sec - global.tv_sec) * 1000000
			+ (now.tv_usec - global.tv_usec));
	pthread_mutex_unlock(mutex);
	return (val / 1000);
}
