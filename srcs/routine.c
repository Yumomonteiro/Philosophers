/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:33:22 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/22 13:29:02 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	someone_died(t_philo *philo)
{
	print_routine(philo, DIE);
        pthread_mutex_lock(&philo->tab->death);
	philo->tab->over = 1;
	philo->dead = 1;
        pthread_mutex_unlock(&philo->tab->death);
	return (1);
}

int	check_death(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(&philo->tab->death);
	now = get_time() - philo->meal;
	if (now >= philo->tab->t_to_die)
	{
		pthread_mutex_unlock(&philo->tab->death);
		return (someone_died(philo));
	}
	pthread_mutex_unlock(&philo->tab->death);
	return (0);
}

void	ft_sleep_and_think(t_philo *philo)
{
	ft_usleep(philo->tab->t_to_sleep);
	print_routine(philo, SLEEP);
	print_routine(philo, THINK);
}

void ft_eat(t_philo *philo)
{
    if (philo->tab->num == 1)
    {
        print_routine(philo, FORK);
        ft_usleep(philo->tab->t_to_die);
        return;
    }

    long int start = get_time();

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        print_routine(philo, FORK);
        pthread_mutex_lock(philo->l_fork);
        print_routine(philo, FORK);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        print_routine(philo, FORK);
        pthread_mutex_lock(philo->r_fork);
        print_routine(philo, FORK);
    }

    pthread_mutex_lock(&philo->tab->death);
    philo->meal = get_time();
    philo->iter_num++;
    pthread_mutex_unlock(&philo->tab->death);

    ft_usleep(philo->tab->t_to_eat);

    if (get_time() - start >= philo->tab->t_to_die)
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        someone_died(philo);
        return;
    }

    print_routine(philo, EAT);
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

int is_turn_or_risk(t_philo *philo)
{
    long int now = get_time();

    pthread_mutex_lock(&philo->tab->death);
    long int time_since_last_meal = now - philo->meal;
    pthread_mutex_unlock(&philo->tab->death);

    if (time_since_last_meal >= philo->tab->t_to_die / 2)
        return 1; // Filosofia em risco força a ação

    pthread_mutex_lock(&philo->tab->turn_mutex);
    int is_turn = (philo->tab->turn == philo->id);
    pthread_mutex_unlock(&philo->tab->turn_mutex);

    return is_turn;
}


void switch_turn(t_philo *philo)
{
    pthread_mutex_lock(&philo->tab->turn_mutex);
    philo->tab->turn = (philo->tab->turn + 1) % philo->tab->num;
    pthread_mutex_unlock(&philo->tab->turn_mutex);
}
void *thread_routine(void *job)
{
    t_philo *philo = (t_philo *)job;

    // Aguarda até que todos os filósofos estejam prontos
    while (1)
    {
        pthread_mutex_lock(&philo->tab->ready_mutex);
        if (philo->tab->ready)
        {
            pthread_mutex_unlock(&philo->tab->ready_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->tab->ready_mutex);
    }

    if (philo->id % 2)
        ft_usleep(philo->tab->t_to_eat * 0.9 + 1);

    while (1)
    {
        pthread_mutex_lock(&philo->tab->death);
        if (philo->tab->over)
        {
            pthread_mutex_unlock(&philo->tab->death);
            break;
        }
        pthread_mutex_unlock(&philo->tab->death);

        if (is_turn_or_risk(philo))
        {
            ft_eat(philo);
            switch_turn(philo);
        }

        if (philo->tab->num == 1)
            break;

        ft_sleep_and_think(philo);

        if (check_death(philo))
            break;
    }

    return (NULL);
}