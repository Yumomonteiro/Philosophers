/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:03:52 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/23 16:51:27 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	check_args(int ac, char *av[])
{
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return (1);
	if (ft_atoi(av[1]) > 200)
		return (1);
	return (0);
}

int	init_philo(t_table *table, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->num)
	{
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].thread_start = 0;
		philo[i].meal = 0;
		philo[i].tab = table;
		philo[i].l_fork = &table->fork[i];
		philo[i].r_fork = 0;
	}
	return (0);
}

static int	init_params_mutex(t_table *table)
{
	int	i;

	i = -1;
	table->fork = 0;
	pthread_mutex_init(&table->death, NULL);
	pthread_mutex_init(&table->ready_mutex, NULL);
	pthread_mutex_init(&table->turn_mutex, NULL);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->num);
	if (!table->fork)
		return (error_msg("Error\nMutex fork: malloc failed\n", table, 0, 1));
	while (++i < table->num)
		if (pthread_mutex_init(&table->fork[i], NULL) == -1)
			return (error_msg("Error\nMutex init failed\n", table, 0, 1));
	return (0);
}

static int	init_var(t_table *table, char **ag)
{
	int	mutex;

	mutex = -1;
	table->num = ft_atoi(ag[1]);
	table->t_to_die = ft_atoi(ag[2]);
	table->t_to_eat = ft_atoi(ag[3]);
	table->t_to_sleep = ft_atoi(ag[4]);
	table->max_eat = -2;
	table->check_meal = 0;
	table->start = 0;
	table->ready = 0;
	table->turn = 0;
	if (ag[5])
	{
		table->check_meal = 1;
		table->max_eat = ft_atoi(ag[5]);
	}
	table->over = 0;
	if (table->num > 0)
		mutex = init_params_mutex(table);
	return (mutex || table->num <= 0 || table->t_to_die <= 0
		|| table->t_to_eat <= 0 || table->t_to_sleep <= 0
		|| table->max_eat == 0);
}

int	main(int ac, char *av[])
{
	t_table	table;

	if (check_args(ac, av) == 1)
		return (printf("\033[0;31mError: invalid args\033[0m\n"), 0);
	if (init_var(&table, av) != 0)
		return (error_msg("Error: invalid arguments\n", &table, 0, 1));
	if (philo(&table))
		return (0);
	return (0);
}
