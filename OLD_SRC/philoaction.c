/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:05 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/19 17:07:40 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	good_sleep(t_philobot *philo)
{
	atomic_print(philo->data, "is sleeping", philo->id);
	usleep(philo->data->sleep_time * 1000);
}

//eat time is edited two time, once when philo start eating
//and once when he is done
void	eat(t_philobot *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&((t_philobot *)philo->next)->fork);
	atomic_print(philo->data, "is eating", philo->id);
	gettimeofday(&philo->last_meal, NULL);
	usleep(philo->data->eat_time * 1000);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&((t_philobot *)philo->next)->fork);
	pthread_mutex_unlock(&philo->fork);
}

int	is_finished(t_philobot *philobot)
{
	int	i;
	int	iteration;

	iteration = philobot[0].data->philo_n;
	i = 0;
	while (i < iteration)
	{
		pthread_mutex_lock(&philobot[i].philodatamutex);
		if (!philobot[i].finished)
		{
			pthread_mutex_unlock(&philobot[i].philodatamutex);
			return (0);
		}
		pthread_mutex_unlock(&philobot[i].philodatamutex);
		i++;
	}
	atomic_print(philobot[0].data, "everyone ate, project finished", -1);
	return (1);
}
