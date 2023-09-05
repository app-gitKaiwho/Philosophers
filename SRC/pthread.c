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
	while (1)
	{
		i = 0;
		gettimeofday(&current, NULL);
		while (i < data->number_of_philobot)
		{
			if (((current.tv_sec - data->philobots[i].lastmeal.tv_sec) * 1000
					+ (current.tv_usec - data->philobots[i].lastmeal.tv_usec)
					/ 1000) > 2000)
			{
				printf("%ldms Philobot %i died\n",
					((current.tv_sec - data->global.tv_sec) * 1000
						+ (current.tv_usec - data->global.tv_usec) / 1000), i);
				return (NULL);
			}
			i++;
		}
	}
}

void	*philobot(void *arg)
{
	t_philobot	*philo;

	philo = (t_philobot *)arg;
	gettimeofday(&philo->lastmeal, NULL);
	printf("Philobot id %d is alive and thinking about life\n", philo->id);
	while (1)
	{
		pthread_mutex_lock(&philo->fourchette);
		printf("Philobot id %d is eating\n", philo->id);
		gettimeofday(&philo->lastmeal, NULL);
		usleep(philo->pdata->time_to_eat);
		philo->Nate++;
		pthread_mutex_unlock(&philo->fourchette);
		if (philo->Nate > philo->pdata->must_eat_n_time)
			return (NULL);
		printf("Philobot id %d ate well\n", philo->id);
	}
}

t_data	init_data(int NPhilo)
{
	t_data	data;

	data.philobots = malloc(sizeof(t_philobot) * NPhilo);
	data.number_of_philobot = NPhilo;
	data.must_eat_n_time = 6;
	data.time_to_die = 2000;
	data.time_to_eat = 200000;
	data.time_to_sleep = 2000;
	while ((--NPhilo) + 1)
	{
		data.philobots[NPhilo].id = NPhilo;
		data.philobots[NPhilo].Nate = 0;
	}
	return (data);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	death;
	int			i;

	i = 0;
	if (ac < 2)
		error_manager(1, "not engnough arg\n");
	data = init_data(ft_atoi(av[1]));
	gettimeofday(&data.global, NULL);
	while (i < ft_atoi(av[1]))
	{
		pthread_create(&(data.philobots[i].thread), NULL, philobot,
			&(data.philobots[i]));
		usleep(1);
		i++;
	}
	pthread_create(&death, NULL, deathripper, &data);
	pthread_join(death, NULL);
	free(data.philobots);
	return (0);
}