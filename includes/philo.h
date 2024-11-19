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
#include <sys/time.h>

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t philo_mutex;
	struct s_table	*table; // Referência à mesa
}				t_philosopher;

typedef struct s_table
{
	pthread_mutex_t	*forks;            // Mutexes para os garfos
	t_philosopher	*philosophers;     // Array de filósofos
	int				num_philo;         // Número de filósofos
	int				t_to_die;          // Tempo para morrer
	int				t_to_eat;          // Tempo para comer
	int 			t_to_think;
	int				t_to_sleep;        // Tempo para dormir
	int				num_phil_must_eat; // Número de refeições necessárias (opcional)
	int				finished_eating;   // Contador de refeições concluídas
	int				simulation_end;    // Flag para indicar o término da simulação
	pthread_mutex_t	print_mutex;       // Mutex para impressões
	pthread_mutex_t	simulation_mutex;  // Mutex para controle da simulação
	long long		start_time;        // Tempo inicial da simulação
}				t_table;

void    ft_usleep(int time);
long long	get_current_time(void);
void	*routine(void *arg);
void log_action(t_philosopher *philosopher, const char *action);
void	join_threads(t_table *table);
void	init_forks_and_philos(t_table *table);
int	init_var(int ac, char **av, t_table *table);
int all_philosophers_ate_enough(t_table *table);
void *monitor(void *arg);
int	create_threads(t_table *table);

#endif
