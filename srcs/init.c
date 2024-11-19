/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:38:14 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/19 18:27:13 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	int	i;

	// Inicializar os parâmetros da mesa com os argumentos fornecidos
	table->num_philo = ft_atoi(av[1]);
	table->t_to_die = ft_atoi(av[2]);
	table->t_to_eat = ft_atoi(av[3]);
	table->t_to_sleep = ft_atoi(av[4]);
	table->num_phil_must_eat = (ac == 6) ? ft_atoi(av[5]) : -1; // Se não for passado, -1
	table->finished_eating = 0;
	table->simulation_end = 0;
	table->t_to_think = 100;

	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->philosophers || !table->forks)
		return (1); // Erro na alocação de memória

	// Inicializar mutexes de garfos
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1); // Erro na inicialização do mutex
		i++;
	}

	// Inicializar mutexes globais
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0 ||
		pthread_mutex_init(&table->simulation_mutex, NULL) != 0)
		return (1);

	// Inicializar filósofos
	i = 0;
	while (i < table->num_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].last_meal_time = get_current_time();
		table->philosophers[i].table = table;
		i++;
	}

	// Registrar o tempo inicial da simulação
	table->start_time = get_current_time();

	return (0); // Sucesso
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL,
			routine, &table->philosophers[i]) != 0)
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}