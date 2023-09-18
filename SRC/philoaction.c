/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvon-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:46:05 by lvon-war          #+#    #+#             */
/*   Updated: 2023/09/12 17:43:58 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

struct timeval	eat(t_data *data, int id, int id_next)
{
	pthread_mutex_lock(&data->philobots[id].fourchette);
	pthread_mutex_lock(&data->philobots[id_next].fourchette);
	printf("Philobot %d is eating with fork %d and %d for the %d time\n",
		id, id, id_next, ++data->philobots[id].n_ate);
	gettimeofday(&data->philobots[id].lastmeal, NULL);
	usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->philobots[id].fourchette);
	pthread_mutex_unlock(&data->philobots[id_next].fourchette);
	return (data->philobots[id].lastmeal);
}

void	smallsleep(t_data *data, int id)
{
	printf("Philobot %d is sleeping\n", id);
	usleep(data->time_to_sleep);
}
