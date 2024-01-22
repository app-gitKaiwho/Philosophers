/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:05 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 15:51:08 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	good_sleep(t_philobot *philo)
{
	atomic_print(philo->data, "is sleeping", philo->id);
	usleep(philo->data->sleep_time);
}

int	eat(t_philobot *philo, int *ate_n)
{
	if (lock_mutex(philo))
	{
		if (lock_mutex(philo->next))
		{
			atomic_print(philo->data, "is eating", philo->id);
			atomic_actualise_time(philo);
			usleep(philo->data->eat_time);
			unlock_mutex(philo);
			unlock_mutex(philo->next);
			if (*ate_n > 0)
				(*ate_n)--;
			atomic_actualise_time(philo);
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

int	eat_odd(t_philobot *philo, int *ate_n)
{
	if (lock_mutex(philo->next))
	{
		if (lock_mutex(philo))
		{
			atomic_print(philo->data, "is eating", philo->id);
			atomic_actualise_time(philo);
			usleep(philo->data->eat_time);
			unlock_mutex(philo->next);
			unlock_mutex(philo);
			if (*ate_n > 0)
				(*ate_n)--;
			atomic_actualise_time(philo);
			atomic_print(philo->data, "is thinking", philo->id);
		}
		else
		{
			unlock_mutex(philo->next);
			return (0);
		}
	}
	else
		return (0);
	return (1);
}
