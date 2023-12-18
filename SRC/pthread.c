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

void	*damocles(void *arg)
{
	t_philobot		*philobots;
	t_data			*data;
	struct timeval	death;	
	int				i;

	philobots = (t_philobot *)arg;
	data = philobots[0].data;
	while (1)
	{
		i = 0;
		if (is_finished((t_philobot *) arg))
			return (NULL);
		gettimeofday(&death, NULL);
		while (i < data->philo_n)
		{
			if (whatttime(philobots[i].last_meal) > data->expiration_time
				&& !philobots[i].finished)
			{
				atomic_print(data, "died", i);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	*philobot(void *arg)
{
	t_data	*data;
	int		ate;

	ate = 0;
	data = ((t_philobot *)arg)->data;
	gettimeofday(&(((t_philobot *)arg)->last_meal), NULL);
	while (1)
	{
		atomic_print(data, "is thinking", ((t_philobot *)arg)->id);
		eat((t_philobot *)arg);
		ate++;
		if (data->flag_eat && ate >= data->min_eat)
		{
			((t_philobot *)arg)->finished = 1;
			return (NULL);
		}
		good_sleep((t_philobot *)arg);
	}
	return (NULL);
}

t_data	*data_fill(char **arg)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	data->philo_n = ft_atoi(arg[1]);
	data->expiration_time = ft_atoi(arg[2]);
	data->eat_time = ft_atoi(arg[3]);
	data->sleep_time = ft_atoi(arg[4]);
	if (ft_wdcount(arg) == 5)
	{
		data->min_eat = ft_atoi(arg[5]);
		data->flag_eat = 1;
	}
	else
		data->flag_eat = 0;
	gettimeofday(&data->global, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (data);
}

t_philobot	*data_init(char **av)
{
	int			i;
	t_data		*data;
	t_philobot	*philobots;

	i = 0;
	data = data_fill(av);
	philobots = malloc(sizeof(t_philobot) * data->philo_n);
	while (i < data->philo_n)
	{
		philobots[i].id = i;
		philobots[i].data = data;
		philobots[i].finished = 0;
		pthread_mutex_init(&philobots[i].fork, NULL);
		if (i == data->philo_n - 1)
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
	t_philobot	*philobots;
	pthread_t	damocles_thread;

	if (ac < 5)
	{
		printf("please provide : [number_of_philosophers] [time_to_die]");
		error_manager(1, " [time_to_eat] [time_to_sleep]\n");
	}
	philobots = data_init(av);
	pthread_create(&damocles_thread, NULL, damocles, philobots);
	pthread_join(damocles_thread, NULL);
	return (0);
}
