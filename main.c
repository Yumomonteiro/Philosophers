/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:03:52 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/19 15:19:58 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// compile if 
// ./philo num_philo "time_to_die" 
//"time_to_eat time_to_sleep" "number_of_times_eat"
//fsanitaze=thread
//valgrind --tool=helgrind
int all_philosophers_ate_enough(t_table *table)
{
    int i;

    for (i = 0; i < table->num_philo; i++)
    {
        if (table->philosophers[i].meals_eaten < table->num_phil_must_eat)
        {
            return 0;  // Se algum filósofo não comeu o número necessário de vezes
        }
    }
    return 1;  // Todos os filósofos comeram o número necessário de vezes
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

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}

void free_resources(t_table *table)
{
    int i;
    for (i = 0; i < table->num_philo; i++)
        pthread_mutex_destroy(&table->forks[i]);

    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->simulation_mutex);
    free(table->forks);
    free(table->philosophers);
}

int main(int ac, char *av[])
{
    t_table table;
    pthread_t monitor_thread;

    if (check_args(ac, av) == 1)
    {
        printf("wrong args\n");
        return (1);
    }
    if (init_var(ac, av, &table) != 0)
    {
        printf("Initialization failed\n");
        return (1);
    }
    if (create_threads(&table) != 0)
    {
        free_resources(&table);
        return (1);
    }

    if (pthread_create(&monitor_thread, NULL, monitor, &table) != 0)
    {
        printf("Error creating monitor thread\n");
        free_resources(&table);
        return (1);
    }

    pthread_join(monitor_thread, NULL);
    
    pthread_mutex_lock(&table.simulation_mutex);
    table.simulation_end = 1;
    pthread_mutex_unlock(&table.simulation_mutex);
    join_threads(&table);
    printf("END OF SIMULATION\n");
    free_resources(&table);
    return (0);
}





