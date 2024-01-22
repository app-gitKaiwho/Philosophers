/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damoclesaction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:20 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 16:41:32 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	everyone_ate(t_philobot *philobots, t_data *data, int i)
{
	if (data->min_eat > 0)
	{
		if (fetch_data(&data->data_mutex, &data->f_eat) >= data->philo_n)
		{
			atomic_print(philobots[i].data, "Everyone finished eating", -1);
			return (1);
		}
	}
	return (0);
}

int	someone_died(t_philobot *philobots, t_data *data, int i)
{
	if (whatttime(&philobots[i].pdata, philobots[i].last_meal)
		>= data->expiration_time)
	{
		atomic_print(philobots[i].data, "died", philobots[i].id);
		atomic_set_data(&data->data_mutex, &data->flag_dead, 1);
		return (1);
	}
	return (0);
}
