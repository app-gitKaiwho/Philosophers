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
	int				i;

	philobots = (t_philobot *)arg;
	data = philobots[0].data;
	while (1)
	{
		i = 0;
		while (i < data->philo_n)
		{
			if (atomic_fetch_data(&philobots[i].pdata, &philobots[i].finished))
				continue ;
			else if (whatttime(&philobots[i].pdata,
					philobots[i].last_meal) > data->expiration_time)
			{
				atomic_print(philobots[i].data, "died", philobots[i].id);
				atomic_set_data(&data->data_mutex, &data->flag_dead, 1);
				return (NULL);
			}
			else if ((atomic_fetch_data(&data->data_mutex,
						&data->f_eat) > data->min_eat && data->min_eat > 0))
			{
				atomic_print(philobots[i].data, "Everyone finished eating", -1);
				return (NULL);
			}
			i++;
		}
	}
}

void	*philobot(void *arg)
{
	t_philobot	*philo;
	int			ate_n;

	philo = (t_philobot *)arg;
	ate_n = atomic_fetch_data(&philo->data->data_mutex, &philo->data->min_eat);
	atomic_print(philo->data, "is thinking", philo->id);
	atomic_actualise_time(philo);
	while (1)
	{
		if (check_death(philo))
		{
			printf("Someone died\n");
			return (NULL);
		}
		if (check_free_fork(philo))
			eat(philo, &ate_n);
		if ((ate_n <= 0 && philo->data->min_eat > 0) || check_death(philo))
		{
			printf("Someone died or I finished\n");
			atomic_set_data(&philo->pdata, &philo->finished, 1);
			atomic_set_data(&philo->data->data_mutex, &philo->data->f_eat,
				atomic_fetch_data(&philo->data->data_mutex, &philo->data->f_eat)
				+ 1);
			return (NULL);
		}
		good_sleep(philo);
	}
}

t_data	*data_fill(char **arg)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_n = ft_atoi(arg[1]);
	data->expiration_time = ft_atoi(arg[2]);
	data->sleep_time = ft_atoi(arg[3]);
	data->eat_time = ft_atoi(arg[4]);
	if (arg[5])
		data->min_eat = ft_atoi(arg[5]);
	else
		data->min_eat = -1;
	data->f_eat = 0;
	data->flag_dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->data_mutex, NULL);
	gettimeofday(&data->global, NULL);
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
	i = 0;
	return (philobots);
}

int	main(int ac, char **av)
{
	t_philobot	*philobots;
	pthread_t	*threads;
	pthread_t	damocles_thread;
	int			i;

	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"));
	philobots = data_init(av);
	if (!philobots)
		return (printf("Malloc error\n"));
	threads = malloc(sizeof(pthread_t) * philobots[0].data->philo_n);
	if (!threads)
		return (printf("Malloc error\n"));
	i = 0;
	while (i < philobots[0].data->philo_n)
	{
		pthread_create(&threads[i], NULL, philobot, &philobots[i]);
		i++;
	}
	i = 0;
	pthread_create(&damocles_thread, NULL, damocles, philobots);
	while (i < philobots[0].data->philo_n)
		pthread_join(threads[i++], NULL);
	pthread_join(damocles_thread, NULL);
	return (0);
}
