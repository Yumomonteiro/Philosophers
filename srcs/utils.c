/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:54:40 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/20 16:05:30 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_routine(t_philo *p, char *action)
{
	pthread_mutex_lock(p->tab->death);
	if (p->tab->over)
	{
		pthread_mutex_unlock(p->tab->death);
		return ;
	}
	printf("%ldms %d %s\n", get_time() - p->thread_start,
		p->id, action);
	pthread_mutex_unlock(p->tab->death);
}

void	final_print(int alive)
{
	printf("						\n");
	if (alive)
		printf("	(☞ﾟヮﾟ)☞ no one died today	\n");
	else
		printf("	¯\\_(ツ)_/¯			\n");
	printf("						\n");
}