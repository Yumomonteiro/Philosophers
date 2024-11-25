/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:43:53 by yude-oli          #+#    #+#             */
/*   Updated: 2024/11/25 11:06:02 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <pthread.h>
# include <sys/stat.h>
# include <sys/time.h>

# define LEFT 0
# define RIGHT 1
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\e[0;31mDIED\e[m"

typedef struct s_table
{
	long int	start;
	int			num;
	int			ready;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	int			max_eat;
	int			check_meal;
	int			over;
	int			turn;
	pthread_mutex_t	turn_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	death;
	pthread_mutex_t	*fork;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		thread_start;
	long int		meal;
	pthread_t		life_tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_table		*tab;
}				t_philo;


void		ft_eat(t_philo *philo);
int		ft_atoi(const char *str);
int		ft_usleep(long int time);
int		philo(t_table *table);
int		init_philo(t_table *table, t_philo *philo);
int		error_msg(char *s, t_table *table, t_philo *philo, int malloc);
void		*thread_routine(void *job);
void		final_print(int alive);
void		print_routine(t_philo *p, char *action);
int		check_death(t_philo *p);
int		init_thread(t_table *table, t_philo *philo);
void		end_thread(t_table *table, t_philo *philo);
long int	get_time(void);
void	take_forks(t_philo *p);
void	return_forks(t_philo *p);

#endif
