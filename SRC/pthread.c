/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvon-war <lvonwar42@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:27:30 by lvon-war          #+#    #+#             */
/*   Updated: 2024/01/22 23:31:59 by lvon-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*damocles(void *arg)
{
	t_philobot		*philobots;
	t_data			*data;
	int				i;

	philobots = (t_philobot *)arg;
	data = philobots[0].data;
	atomic_print(data, "Death is watching", -1);
	while (1)
	{
		i = 0;
		while (i < data->philo_n)
		{
			if (everyone_ate(philobots, data, i))
				return (NULL);
			if (fetch_data(&philobots[i].pdata, &philobots[i].finished))
				continue ;
			else if (someone_died(philobots, data, i))
				return (NULL);
			i++;
		}
	}
}

void	*philobot(void *arg)
{
	t_philobot	*philo;
	int			ate_n;
	int			ate;

	philo = (t_philobot *)arg;
	ate_n = fetch_data(&philo->data->data_mutex, &philo->data->min_eat);
	atomic_print(philo->data, "Woke up", philo->id);
	atomic_actualise_time(philo);
	if (!philo->id % 2)
		usleep(philo->data->eat_time / 2);
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		ate = eat(philo, &ate_n);
		if ((ate_n <= 0 && philo->data->min_eat > 0) || check_death(philo))
		{
			atomic_set_data(&philo->pdata, &philo->finished, 1);
			atomic_set_data(&philo->data->data_mutex, &philo->data->f_eat,
				fetch_data(&philo->data->data_mutex, &philo->data->f_eat) + 1);
			return (NULL);
		}
		if (ate && !check_death(philo))
			good_sleep(philo);
	}
}

void	process(pthread_t	*threads, t_philobot *philobots)
{
	int	i;

	i = -1;
	while (++i < philobots[0].data->philo_n)
	{		
		pthread_create(&threads[i], NULL, philobot, &philobots[i]);
		usleep(100);
	}
	pthread_create(&threads[i], NULL, damocles, philobots);
	i = 0;
	while (i < philobots[0].data->philo_n + 1)
		pthread_join(threads[i++], NULL);
}
