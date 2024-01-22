/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:05 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 14:19:15 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	good_sleep(t_philobot *philo)
{
	atomic_print(philo->data, "is sleeping", philo->id);
	usleep(philo->data->sleep_time);
}

void	eat(t_philobot *philo, int *ate_n)
{
	pthread_mutex_lock(&philo->fork);
	atomic_set_data(&philo->pdata, &philo->fork_locked, 1);
	pthread_mutex_lock(&philo->next->fork);
	atomic_set_data(&philo->next->pdata, &philo->next->fork_locked, 1);
	atomic_print(philo->data, "is eating", philo->id);
	atomic_actualise_time(philo);
	atomic_set_data(&philo->pdata, &philo->fork_locked, 0);
	pthread_mutex_unlock(&philo->fork);
	atomic_set_data(&philo->next->pdata, &philo->next->fork_locked, 0);
	pthread_mutex_unlock(&philo->next->fork);
	if (*ate_n > 0)
		(*ate_n)--;
	atomic_print(philo->data, "is thinking", philo->id);
}
