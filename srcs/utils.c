/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:54:40 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/21 14:59:57 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_routine(t_philo *p, char *action)
{
	pthread_mutex_lock(p->tab->death);
	if (!p->tab->over)
	{
                printf("%ldms %d %s\n", get_time() - p->thread_start,
                        p->id, action);
		// pthread_mutex_unlock(p->tab->death);
		// return ;
	}
	pthread_mutex_unlock(p->tab->death);
}

void	final_print(int alive)
{
	printf("						\n");
	if (alive)
		printf("	😎	       \n");
	else
		printf("	😵    \n");
	printf("						\n");
}