/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:03:52 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/20 15:58:24 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// compile if 
// ./philo num_philo "time_to_die" 
//"time_to_eat time_to_sleep" "number_of_times_eat"
//fsanitaze=thread
//valgrind --tool=helgrind
int	error_msg(char *s, t_table *table, t_philo *philo, int malloc)
{
	if (malloc)
	{
		if (table->death)
			free(table->death);
		if (table->fork)
			free(table->fork);
		if (philo)
			free(philo);
	}		
	return (printf("%s", s));
}
int	check_args(int ac, char *av[])
{
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <=0
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
		philo[i].id = i;
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
	table->death = 0;
	table->fork = 0;
	table->death = malloc(sizeof(pthread_mutex_t));
	if (!table->death)
		return (error_msg("Error\nMutex death: malloc failed\n", table, 0, 1));
	table->fork = malloc(sizeof(pthread_mutex_t) * table->num);
	if (!table->fork)
		return (error_msg("Error\nMutex fork: malloc failed\n", table, 0, 1));
	if (pthread_mutex_init(table->death, NULL) == -1)
		return (error_msg("Error\nMutex init failed\n", table, 0, 1));
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
	table->max_iter = -2;
	table->check_meal = 0;
	table->start = 0;
	table->ready = 0;
	if (ag[5])
	{
		table->check_meal = 1;
		table->max_iter = ft_atoi(ag[5]);
	}
	table->over = 0;
	if (table->num > 0)
		mutex = init_params_mutex(table);
	return (mutex || table->num <= 0 || table->t_to_die <= 0 || table->t_to_eat <= 0
		|| table->t_to_sleep <= 0 || table->max_iter == 0);
}
int    ft_error(void)
{
    printf("\033[0;31mError : invalid arguments\033[0m\n");
    return (0);
}
int main(int ac, char *av[])
{
   t_table table;

    if (check_args(ac, av) == 1 || init_var(&table, av) != 0)
        return (error_msg("Error: invalid arguments\n", &table, 0, 1));
    if (philo(&table))
        return(0);
    return (0);
}





