/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:33:22 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/20 16:07:17 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	someone_died(t_philo *philo)
{
	print_routine(philo, DIE);
	philo->tab->over = 1;
	philo->dead = 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (1);
}

int	check_death(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(philo->tab->death);
	now = get_time() - philo->meal;
	if (now >= philo->tab->t_to_die)
	{
		pthread_mutex_unlock(philo->tab->death);
		return (someone_died(philo));
	}
	pthread_mutex_unlock(philo->tab->death);
	return (0);
}

void	ft_sleep_and_think(t_philo *philo)
{
	ft_usleep(philo->tab->t_to_sleep);
	print_routine(philo, SLEEP);
	print_routine(philo, THINK);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_routine(philo, FORK);
	pthread_mutex_lock(philo->r_fork);
	print_routine(philo, FORK);
	philo->meal = get_time();
	ft_usleep(philo->tab->t_to_eat);
	print_routine(philo, EAT);
	philo->iter_num++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*thread_routine(void *job)
{
	t_philo	*philo;

	philo = (t_philo *)job;
	while (!philo->tab->ready)
		continue ;
	if (philo->id & 1)
		ft_usleep(philo->tab->t_to_eat * 0.9 + 1);
	while (!philo->tab->over)
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	return (NULL);
}
