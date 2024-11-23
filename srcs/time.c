/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:35:18 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/23 16:38:40 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time)
		usleep(100);
	return (1);
}

int	error_msg(char *s, t_table *table, t_philo *philo, int malloc)
{
	if (malloc)
	{
		if (table->fork)
			free(table->fork);
		if (philo)
			free(philo);
	}
	return (printf("%s", s));
}
