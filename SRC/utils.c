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

int	error_manager(int err_code, char *err_msg)
{
	printf("%s\n", err_msg);
	exit(err_code);
}

long	whatttime(struct timeval global)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - global.tv_sec) * 1000
		+ (now.tv_usec - global.tv_usec) / 1000);
}

void	atomic_print(t_data *data, char *txt, int id)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ldms id[%d] %s\n", whatttime(data->global), id, txt);
	pthread_mutex_unlock(&data->print_mutex);
}
