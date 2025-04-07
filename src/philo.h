/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:38:49 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/03 10:38:49 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/* MUTEX OPCODES

	LOCK = 0
	UNLOCK = 1
	INIT = 2
	DESTROY = 3

*/

/* THREAD OPCODES

	CREATE = 0
	JOIN = 1
	DETACH = 2

*/

/* ACTION OPCODES

	DIED = 0
	EATING = 1
	SLEEPING = 2
	THINKING = 3
	TOOK_FIRST_FORK = 4
	TOOK_SECOND_FOR = 5

*/

// Color

# define RST	"\033[0m"
# define R		"\033[1;31mm"
# define G		"\033[1;32mm"
# define Y		"\033[1;33mm"

// Structures

typedef pthread_mutex_t	t_mutex;

typedef struct s_data 	t_data;

typedef struct			s_fork
{
	t_mutex	fork_mutex;
	int		fork_id;
}						t_fork;

typedef struct			s_philo
{
	int			id;
	pthread_t	philo_thread_id;
	long		meal_count;
	int			full;
	long		time_last_meal;
	t_mutex		philo_mutex;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*input;
}						t_philo;

struct					s_data
{
	long	nbr_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_start;
	int		end_program;
	long	nbr_max_meals;
	int		all_threads_ready;
	t_mutex	data_mutex;
	t_mutex	write_mutex;
	t_fork	*forks;
	t_philo	*philos;
};

// Prototypes
// ·· Main functions

int		parse_input(t_data *input, char **argv);
long	timestamp(void);
void	error_exit(char *error);
void	data_init(t_data *input);
void	free_all(t_data *data);

// ·· Safe functions

void	safe_mutex(t_mutex *mutex, int opcode);
void	*safe_malloc(size_t bytes);
void	safe_thread(pthread_t *philo_thread_id, void *(*function)(void *),
					t_philo *philos, int opcode);

// ·· Setters / Getters

void	set_status(t_mutex *mutex, int *status, int value);
void	set_long(t_mutex *mutex, long *number, long value);
int		get_status(t_mutex *mutex, int *status);
long	get_long(t_mutex *mutex, long *number);
void	wait_all_threads_ready(t_data *input);

// ·· Dinner simulation

void	dinner_start(t_data *input);
void	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	think(t_philo *philo);
void	write_action(int action, t_philo *philo);

#endif