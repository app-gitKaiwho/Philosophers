/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:05 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/23 16:36:39 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	good_sleep(t_philobot *philo)
{
	atomic_print(philo->data, "is sleeping", philo->id);
	usleep(philo->data->sleep_time);
	atomic_print(philo->data, "is thinking", philo->id);
}

int	eat_even(t_philobot *philo, int *ate_n)
{
	if (lock_mutex(philo))
	{
		if (lock_mutex(philo->next))
		{
			atomic_actualise_time(philo);
			atomic_print(philo->data, "is eating", philo->id);
			usleep(philo->data->eat_time);
			unlock_mutex(philo);
			unlock_mutex(philo->next);
			if (*ate_n > 0)
				(*ate_n)--;
			if (fetch_data(&philo->data->data_mutex, &philo->data->flag_dead))
				return (0);
			atomic_print(philo->data, "is thinking", philo->id);
		}
		else
		{
			unlock_mutex(philo);
			return (0);
		}
	}
	else
		return (0);
	return (1);
}

int	eat(t_philobot *philo, int *ate_n)
{	
	if (philo->data->philo_n % 2 == 0)
		return (eat_even(philo, ate_n));
	if (lock_mutex(philo))
	{
		while (!lock_mutex(philo->next))
		{
			if (check_death(philo))
			{
				unlock_mutex(philo);
				return (0);
			}
		}
		atomic_print(philo->data, "is eating", philo->id);
		atomic_actualise_time(philo);
		usleep(philo->data->eat_time);
		unlock_mutex(philo);
		unlock_mutex(philo->next);
		if (*ate_n > 0)
			(*ate_n)--;
	}
	else
		return (0);
	return (1);
}
