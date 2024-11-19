/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:33:22 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/19 18:30:42 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
void    ft_usleep(int time)
{
    long long i = 0;
    i = get_current_time() + time;
    while(get_current_time() <= i)
    {
        usleep(500);
    }
    
}
void *routine(void *arg)
{
    t_philosopher *philosopher = (t_philosopher *)arg;
    t_table *table = philosopher->table;

    while (1)
    {
        // Verifica se a simulação acabou
        pthread_mutex_lock(&table->simulation_mutex);
        if (table->simulation_end)
        {
            pthread_mutex_unlock(&table->simulation_mutex);
            return NULL; // Sai da thread
        }
        pthread_mutex_unlock(&table->simulation_mutex);

        // Caso especial: Apenas 1 filósofo
        if (table->num_philo == 1)
        {
            ft_usleep(table->t_to_die * 1000); // Espera até "morrer"
            continue; // Não tenta pegar garfos
        }

        // Pensando
        log_action(philosopher, "is thinking");
        usleep(table->t_to_think * 1000);

        // Pegando os garfos
        pthread_mutex_lock(&table->forks[philosopher->id - 1]);
        log_action(philosopher, "has taken a fork");
        pthread_mutex_lock(&table->forks[philosopher->id % table->num_philo]);
        log_action(philosopher, "has taken a fork");

        // Comendo
        log_action(philosopher, "is eating");
        philosopher->last_meal_time = get_current_time();
        philosopher->meals_eaten++;
        usleep(table->t_to_eat * 1000);

        // Devolvendo os garfos
        pthread_mutex_unlock(&table->forks[philosopher->id % table->num_philo]);
        pthread_mutex_unlock(&table->forks[philosopher->id - 1]);

        // Dormindo
        log_action(philosopher, "is sleeping");
        usleep(table->t_to_sleep * 1000);
    }
    return NULL;
}
