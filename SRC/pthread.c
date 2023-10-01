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

void	*philobot(void *arg)
{
	t_data	*data;

	data = ((t_philobot *)arg)->data;
	atomic_print(data, "woke up", ((t_philobot *)arg)->id);
	eat((t_philobot *)arg);
	good_sleep((t_philobot *)arg);
	atomic_print(data, "finished", ((t_philobot *)arg)->id);
	return (NULL);
}

t_data	*data_fill(void)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	data->sleep_time = 100;
	data->eat_time = 100;
	data->expiration_time = 200;
	data->min_eat = 2;
	gettimeofday(&data->global, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (data);
}

t_philobot	*data_init(int n)
{
	int			i;
	t_data		*data;
	t_philobot	*philobots;

	i = 0;
	data = data_fill();
	philobots = malloc(sizeof(t_philobot) * n);
	while (i < n)
	{
		philobots[i].id = i;
		philobots[i].data = data;
		gettimeofday(&philobots[i].last_meal, NULL);
		pthread_mutex_init(&philobots[i].fork, NULL);
		if (i == n - 1)
			philobots[i].next = &philobots[0];
		else
			philobots[i].next = &philobots[i + 1];
		pthread_create(&philobots[i].thread, NULL, philobot, &philobots[i]);
		i++;
	}
	return (philobots);
}

int	main(int ac, char **av)
{
	t_philobot	*data;
	int		i;

	i = 0;
	if (ac < 2)
		error_manager(1, "not engnough arg\n");
	data = data_init(ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		pthread_join(data[i].thread, NULL);
		i++;
	}
	return (0);
}
