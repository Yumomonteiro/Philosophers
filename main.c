/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:03:52 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/09 14:27:23 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
// compile if 
// ./philo num_philo "time_to_die" 
//"time_to_eat time_to_sleep" "number_of_times_eat"
//fsanitaze=thread
//valgrind --tool=helgrind

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

void	init_forks_and_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->num_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].table = table;
		i++;
	}
}
int	init_var(int ac, char **av, t_table *table)
{
	table->num_philo = ft_atoi(av[1]);
	table->t_to_die = ft_atoi(av[2]);
	table->t_to_eat = ft_atoi(av[3]);
	table->t_to_sleep = ft_atoi(av[4]);
	table->num_phil_must_eat = 0;
	if (ac == 6)
		table->num_phil_must_eat = ft_atoi(av[5]);
	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philo);
	table->forks = malloc(sizeof(t_table) * table->num_philo);
	if (!table->philosophers || !table->forks)
		return (1);
	init_forks_and_philos(table);
	pthread_mutex_init(&table->print_mutex, NULL);
	return (0);
}

int	main(int ac, char *av[])
{
	t_table	table;

	if (check_args(ac, av) == 1)
	{
		printf("wrong args\n");
		return (0);
	}
	if (init_var(ac, av, &table) == 0)
	{

	}
	//free_all function
	return (0);
}