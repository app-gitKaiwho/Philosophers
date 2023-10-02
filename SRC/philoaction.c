/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:05 by lvon-war          #+#    #+#             */
/*   Updated: 2023/10/02 09:07:19 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	good_sleep(t_philobot *philo)
{
	atomic_print(philo->data, "is sleeping", philo->id);
	usleep(philo->data->sleep_time * 1000);
}

void	eat(t_philobot *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&((t_philobot *)philo->next)->fork);
	atomic_print(philo->data, "is eating", philo->id);
	usleep(philo->data->eat_time * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&((t_philobot *)philo->next)->fork);
}
