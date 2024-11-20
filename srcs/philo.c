/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:25:38 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/20 16:06:39 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_meals(t_philo p, int last)
{
	if (p.tab->check_meal
		&& last == p.tab->num - 1
		&& p.iter_num == p.tab->max_iter)
		return (ft_usleep(300));
	return (0);
}

static void	check_thread(t_table *table, t_philo *philo)
{
	int	i;

	while (!table->ready)
		continue ;
	while (!table->over)
	{
		i = -1;
		while (++i < table->num)
			if (check_death(&philo[i]) || check_meals(philo[i], i))
				table->over = 1;
	}
	if (table->check_meal && philo[table->num - 1].iter_num == table->max_iter)
	{
		ft_usleep(5 * table->num);
		printf("						\n");
		printf("  All philosophers have eaten %d times\n", table->max_iter);
		return (final_print(1));
	}
	return (final_print(0));
}

static int	init_thread(t_table *table, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->num)
	{
		philo[i].r_fork = philo[(i + 1) % table->num].l_fork;
		if (pthread_create(&philo[i].life_tid, NULL,
				&thread_routine, &philo[i]) == -1)
			return (error_msg("Error\nFailed to create thread\n", table, philo, 2));
	}
	i = -1;
	table->start = get_time();
	while (++i < table->num)
	{
		philo[i].thread_start = table->start;
		philo[i].meal = table->start;
	}
	table->ready = 1;
	return (0);
}

static void	end_thread(t_table *table, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->num)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(table->death);
	pthread_mutex_destroy(table->fork);
	free(table->death);
	free(table->fork);
	free(philo);
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