#ifndef PHILO_H
# define PHILO_H

# include "../libs/libft/libft.h"
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

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_table	*table; // ponteiro para a mesa para acesso compartilhado
}				t_philosopher;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				num_phil_must_eat;
	int				num_philo;
	long long		start_time;
	pthread_mutex_t	print_mutex;
}				t_table;

#endif
