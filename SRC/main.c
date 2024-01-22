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

t_data	*data_fill(char **arg)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_n = ft_atoi(arg[1]);
	data->expiration_time = ft_atoi(arg[2]);
	data->eat_time = ft_atoi(arg[3]) * 1000;
	data->sleep_time = ft_atoi(arg[4]) * 1000;
	if (arg[5])
		data->min_eat = ft_atoi(arg[5]);
	else
		data->min_eat = -1;
	data->f_eat = 0;
	data->flag_dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->data_mutex, NULL);
	return (data);
}

t_philobot	*data_init(char **av)
{
	int			i;
	t_data		*data;
	t_philobot	*philobots;

	i = 0;
	data = data_fill(av);
	if (!data)
		return (NULL);
	philobots = malloc(sizeof(t_philobot) * data->philo_n);
	if (!philobots)
		return (NULL);
	while (i < data->philo_n)
	{
		philobots[i].data = data;
		philobots[i].id = i;
		philobots[i].finished = 0;
		philobots[i].fork_locked = 0;
		pthread_mutex_init(&philobots[i].pdata, NULL);
		pthread_mutex_init(&philobots[i].fork, NULL);
		philobots[i].next = &philobots[(i + 1) % data->philo_n];
		i++;
	}
	return (philobots);
}

int	main(int ac, char **av)
{
	t_philobot	*philobots;
	pthread_t	*threads;

	if (ac < 5 || ac > 6)
	{
		printf("please provide : [number_of_philosophers] [time_to_die]");
		printf(" [time_to_eat] [time_to_sleep]\n");
		return (1);
	}
	else
	{
		philobots = data_init(av);
		if (!philobots)
			return (printf("Malloc error\n"));
		threads = malloc(sizeof(pthread_t) * philobots[0].data->philo_n + 1);
		if (!threads)
			return (printf("Malloc error\n"));
		gettimeofday(&philobots[0].data->global, NULL);
		process(threads, philobots);
		free_all(philobots, threads);
	}
	return (0);
}
