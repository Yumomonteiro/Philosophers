/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:25:38 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/25 11:13:14 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_meals(t_philo p, int last)
{
	if (p.tab->check_meal
		&& last == p.tab->num - 1
		&& p.iter_num == p.tab->max_eat)
		return (ft_usleep(300));
	return (0);
}

static void	sinc_threads(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->ready_mutex);
		if (table->ready)
		{
			pthread_mutex_unlock(&table->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->ready_mutex);
	}
}

static void	check_thread_over(t_table *table, t_philo *philo)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&table->death);
		if (table->over)
		{
			pthread_mutex_unlock(&table->death);
			break ;
		}
		pthread_mutex_unlock(&table->death);
		i = -1;
		while (++i < table->num)
		{
			if (check_death(&philo[i]) || check_meals(philo[i], i))
			{
				pthread_mutex_lock(&table->death);
				table->over = 1;
				pthread_mutex_unlock(&table->death);
				break ;
			}
		}
	}
}

static void	check_thread(t_table *table, t_philo *philo)
{
	sinc_threads(table);
	check_thread_over(table, philo);
	if (table->check_meal && philo[table->num - 1].iter_num == table->max_eat)
		return ;
	return ;
}

int	philo(t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * table->num);
	if (!philo || init_philo(table, philo))
		return (EXIT_FAILURE);
	if (init_thread(table, philo))
		return (EXIT_FAILURE);
	check_thread(table, philo);
	end_thread(table, philo);
	return (0);
}
