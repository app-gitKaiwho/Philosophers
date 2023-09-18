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

	data = (t_data *)arg;
	pthread_mutex_lock(&(data->data));
	data->compteur++;
	pthread_mutex_unlock(&(data->data));
	return (NULL);
}

t_data	data_init(t_data data, int n)
{
	int	i;

	i = 0;
	data.philobots = malloc(sizeof(t_philobot) * n);
	data.compteur = 0;
	printf("%d\n", data.compteur);
	while (i < n)
	{
		pthread_create(&(data.philobots[i].thread), NULL, philobot, &data);
		i++;
	}
	return (data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac < 2)
		error_manager(1, "not engnough arg\n");
	data = data_init(data, ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		pthread_join(data.philobots[i].thread, NULL);
		i++;
	}
	printf("%d\n", data.compteur);
	return (0);
}
