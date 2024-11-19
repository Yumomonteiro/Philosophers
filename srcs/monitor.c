/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:34:29 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/19 17:40:00 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *monitor(void *arg)
{
    t_table *table = (t_table *)arg;
    usleep(6000);
    
    while (1)
    {
        pthread_mutex_lock(&table->simulation_mutex);

        // Encerrar o monitor se a simulação já tiver acabado
        if (table->simulation_end == 1)
        {
            pthread_mutex_unlock(&table->simulation_mutex);
            return NULL;
        }

        // Caso especial: Apenas 1 filósofo
        if (table->num_philo == 1)
        {
            if (get_current_time() - table->philosophers[0].last_meal_time > table->t_to_die)
            {
                pthread_mutex_lock(&table->print_mutex);
                printf("\033[0;31m%lld %d died\033[0m\n",
                       get_current_time() - table->start_time, table->philosophers[0].id);
                table->simulation_end = 1; // Encerrar a simulação
                pthread_mutex_unlock(&table->print_mutex);
                pthread_mutex_unlock(&table->simulation_mutex);
                return NULL;
            }
        }

        // Verificar se algum filósofo morreu
        for (int i = 0; i < table->num_philo; i++)
        {
            usleep(1000);
            //preciso de lockar o fiosofo para poder olhar para o last_meal_time
            if (get_current_time() - table->philosophers[i].last_meal_time > table->t_to_die)
            {
                pthread_mutex_lock(&table->print_mutex);
                printf("\033[0;31m%lld %d died\033[0m\n",
                       get_current_time() - table->start_time, table->philosophers[i].id);
                table->simulation_end = 1;
                pthread_mutex_unlock(&table->print_mutex);
                pthread_mutex_unlock(&table->simulation_mutex);
                return NULL;
            }
        }

        // Verificar se todos comeram o suficiente
        if (table->num_phil_must_eat != -1 && all_philosophers_ate_enough(table))
        {
            table->simulation_end = 1;
        }

        pthread_mutex_unlock(&table->simulation_mutex);
        usleep(1000); // Pequeno atraso para evitar alto uso de CPU
    }
}
