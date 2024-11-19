/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:37:46 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/19 15:48:58 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void log_action(t_philosopher *philosopher, const char *action)
{
    t_table *table = philosopher->table;
	
    pthread_mutex_lock(&table->print_mutex);
	if(table->simulation_end == 0)
		printf("%lld %d %s\n",
			get_current_time() - table->start_time,
			philosopher->id,
			action);
    pthread_mutex_unlock(&table->print_mutex);
}