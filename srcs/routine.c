/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:33:22 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/23 16:38:11 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	someone_died(t_philo *philo)
{
	print_routine(philo, DIE);
	pthread_mutex_lock(&philo->tab->death);
	philo->tab->over = 1;
	philo->dead = 1;
	pthread_mutex_unlock(&philo->tab->death);
	return (1);
}

int	check_death(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(&philo->tab->death);
	now = get_time() - philo->meal;
	if (now >= philo->tab->t_to_die)
	{
		pthread_mutex_unlock(&philo->tab->death);
		return (someone_died(philo));
	}
	pthread_mutex_unlock(&philo->tab->death);
	return (0);
}

void	ft_sleep_and_think(t_philo *philo)
{
	ft_usleep(philo->tab->t_to_sleep);
	print_routine(philo, SLEEP);
	print_routine(philo, THINK);
}

void	*philo_routine(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo))
			break ;
		pthread_mutex_lock(&philo->tab->death);
		if (philo->tab->over)
		{
			pthread_mutex_unlock(&philo->tab->death);
			break ;
		}
		pthread_mutex_unlock(&philo->tab->death);
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	return (0);
}

void	*thread_routine(void *job)
{
	t_philo	*philo;

	philo = (t_philo *)job;
	while (1)
	{
		pthread_mutex_lock(&philo->tab->ready_mutex);
		if (philo->tab->ready)
		{
			pthread_mutex_unlock(&philo->tab->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->tab->ready_mutex);
	}
	if (philo->id % 2)
		ft_usleep(philo->tab->t_to_eat * 0.9 + 1);
	philo_routine(philo);
	return (NULL);
}
