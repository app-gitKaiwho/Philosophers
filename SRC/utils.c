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
		if (fetch_data(&philobot[i].pdata, &philobot[i].finished))
			return (0);
		i++;
	}
	atomic_print(philobot[0].data, "everyone ate, project finished", -1);
	return (1);
}

int	lock_mutex(t_philobot *philo)
{
	if (fetch_data(&philo->pdata, &philo->fork_locked))
		return (0);
	atomic_set_data(&philo->pdata, &philo->fork_locked, 1);
	pthread_mutex_lock(&philo->fork);
	return (1);
}

void	unlock_mutex(t_philobot *philo)
{
	atomic_set_data(&philo->pdata, &philo->fork_locked, 0);
	pthread_mutex_unlock(&philo->fork);
}

void	free_all(t_philobot *philobot, pthread_t *threads)
{
	int	i;
	int	iteration;

	iteration = philobot[0].data->philo_n;
	i = 0;
	while (philobot && i < iteration)
	{
		pthread_mutex_destroy(&philobot[i].pdata);
		pthread_mutex_destroy(&philobot[i].fork);
		i++;
	}
	i = -1;
	while (threads && ++i < philobot[0].data->philo_n + 1)
		free(threads);
	pthread_mutex_destroy(&philobot[0].data->print_mutex);
	pthread_mutex_destroy(&philobot[0].data->data_mutex);
	free(philobot[0].data);
	free(philobot);
}
