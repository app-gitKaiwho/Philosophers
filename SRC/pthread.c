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

void	*deathripper(void *arg)
{
	t_data			*data;
	struct timeval	current;
	int				i;

	data = (t_data *)arg;
	usleep(data->time_to_die - 500);
	while (1)
	{
		i = 0;
		gettimeofday(&current, NULL);
		while (i < data->number_of_philobot)
		{
			if ((current.tv_sec - data->philobots[i].lastmeal.tv_sec)
				>= (data->time_to_die / 1000000) && data->philobots[i].n_ate
				< data->must_eat_n_time)
			{
				printf("philobot %d died\n", i);
				return (NULL);
			}
			i++;
		}
	}
}

void	*philobot(void *arg)
{
	t_data		*data;
	t_folder	*f;
	t_philobot	*philo;

	f = (t_folder *)arg;
	data = &f->data;
	philo = &data->philobots[f->id_philo];
	gettimeofday(&philo->lastmeal, NULL);
	printf("philobot %d rose from the void\n", f->id_philo);
	while (1)
	{
		printf("philobot %d is thinking\n", f->id_philo);
		philo->lastmeal = eat(data, f->id_philo, f->id_next);
		if (philo->n_ate >= data->must_eat_n_time)
			return (NULL);
		smallsleep(data, f->id_philo);
	}
}

t_data	init_data(int NPhilo)
{
	t_data	data;

	data.philobots = malloc(sizeof(t_philobot) * NPhilo);
	data.number_of_philobot = NPhilo;
	data.must_eat_n_time = 5;
	data.time_to_die = 8 * 1000 * 1000;
	data.time_to_eat = 2 * 1000 * 1000;
	data.time_to_sleep = 1 * 1000 * 1000;
	while ((--NPhilo) + 1)
	{
		data.philobots[NPhilo].id = NPhilo;
		data.philobots[NPhilo].n_ate = 0;
		pthread_mutex_init(&data.philobots[NPhilo].fourchette, NULL);
		if (pthread_create(&data.philobots[i].thread, NULL, &philobot,
				&(t_folder){data, i, i + 1}) != 0)
			error_manager(1, "Erreur lors de la création du thread\n");
	}
	return (data);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	death;
	int			i;
	char		tmp;

	if (ac < 2)
		error_manager(1, "not engnough arg\n");
	data = init_data(ft_atoi(av[1]));
	gettimeofday(&data.global, NULL);
	pthread_create(&death, NULL, deathripper, &data);
	pthread_join(death, NULL);
	free(data.philobots);
	return (0);
}
