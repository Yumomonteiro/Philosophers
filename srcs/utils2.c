/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:55:19 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/25 11:08:03 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *p)
{
	if (p->tab->num % 2 == 0)
	{
		if (p->id % 2)
		{
			pthread_mutex_lock(p->r_fork);
			print_routine(p, "has taken a fork");
			pthread_mutex_lock(p->l_fork);
			print_routine(p, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(p->l_fork);
			print_routine(p, "has taken a fork");
			pthread_mutex_lock(p->r_fork);
			print_routine(p, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(p->l_fork);
		print_routine(p, "has taken a fork");
		pthread_mutex_lock(p->r_fork);
		print_routine(p, "has taken a fork");
	}
}

void	return_forks(t_philo *p)
{
	if (p->tab->num % 2 == 0)
	{
		if (p->id % 2)
		{
			pthread_mutex_unlock(p->l_fork);
			pthread_mutex_unlock(p->r_fork);
		}
		else
		{
			pthread_mutex_unlock(p->r_fork);
			pthread_mutex_unlock(p->l_fork);
		}
	}
	else
	{
		pthread_mutex_unlock(p->r_fork);
		pthread_mutex_unlock(p->l_fork);
	}
}
