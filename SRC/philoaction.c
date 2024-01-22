/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:05 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 23:31:07 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	good_sleep(t_philobot *philo)
{
	atomic_print(philo->data, "is sleeping", philo->id);
	usleep(philo->data->sleep_time);
	atomic_print(philo->data, "is thinking", philo->id);
}

int	eat(t_philobot *philo, int *ate_n)
{
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
