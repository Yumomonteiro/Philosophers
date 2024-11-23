/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:54:40 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/23 17:03:25 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_routine(t_philo *p, char *action)
{
	pthread_mutex_lock(&p->tab->death);
	if (!p->tab->over)
	{
		printf("%ldms %d %s\n", get_time() - p->thread_start,
			p->id, action);
	}
	pthread_mutex_unlock(&p->tab->death);
}

int	init_thread(t_table *table, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->num)
	{
		philo[i].r_fork = philo[(i + 1) % table->num].l_fork;
		if (pthread_create(&philo[i].life_tid, NULL,
				&thread_routine, &philo[i]) == -1)
			return (error_msg("Failed to create thread\n", table, philo, 2));
	}
	i = -1;
	table->start = get_time();
	while (++i < table->num)
	{
		philo[i].thread_start = table->start;
		philo[i].meal = table->start;
	}
	pthread_mutex_lock(&table->ready_mutex);
	table->ready = 1;
	pthread_mutex_unlock(&table->ready_mutex);
	return (0);
}

void	end_thread(t_table *table, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->num)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(&table->death);
	pthread_mutex_destroy(table->fork);
	pthread_mutex_destroy(&table->ready_mutex);
	pthread_mutex_destroy(&table->turn_mutex);
	free(table->fork);
	free(philo);
}

void	ft_eat(t_philo *philo)
{
	if (philo->tab->num == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_routine(philo, FORK);
		ft_usleep(philo->tab->t_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_routine(philo, FORK);
	pthread_mutex_lock(philo->l_fork);
	print_routine(philo, FORK);
	pthread_mutex_lock(&philo->tab->death);
	philo->meal = get_time();
	philo->iter_num++;
	pthread_mutex_unlock(&philo->tab->death);
	ft_usleep(philo->tab->t_to_eat);
	print_routine(philo, EAT);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
