/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:30:13 by lvon-war          #+#    #+#             */
/*   Updated: 2023/05/26 18:30:13 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	check_free_fork(t_philobot *philo)
{
	int	test;

	test = 0;
	pthread_mutex_lock(&philo->pdata);
	test = philo->fork_locked;
	pthread_mutex_unlock(&philo->pdata);
	pthread_mutex_lock(&philo->next->pdata);
	test |= philo->next->fork_locked;
	pthread_mutex_unlock(&philo->next->pdata);
	return (!test);
}

int	check_death(t_philobot *philo)
{
	int	test;

	test = 0;
	pthread_mutex_lock(&philo->data->data_mutex);
	test = philo->data->flag_dead;
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (test);
}

int	is_finished(t_philobot *philobot)
{
	int	i;
	int	iteration;

	iteration = philobot[0].data->philo_n;
	i = 0;
	while (i < iteration)
	{
		if (atomic_fetch_data(&philobot[i].pdata, &philobot[i].finished))
			return (0);
		i++;
	}
	atomic_print(philobot[0].data, "everyone ate, project finished", -1);
	return (1);
}
