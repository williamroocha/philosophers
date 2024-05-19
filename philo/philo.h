/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:17:55 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/19 19:53:28 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

/* ************************************************************************** */
# define DEFAULT "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
/* ************************************************************************** */

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DIED,
}						t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	bool				full;
	long				meals_counter;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				philo_nbr;
	long				start_dinner;
	bool				end_dinner;
	bool				all_philos_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
};

// Parsing
void					parse(t_table *table, char **av);

// Init
void					init(t_table *table);

// Sync
void					wait_all_philos(t_table *table);
void					increase_long(t_mtx *mutex, long *value);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
// Dinner
void					dinner(t_table *table);

// Ptrhead

void					ft_thread_handler(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);
void					ft_mutex_handler(t_mtx *mutex, t_opcode opcode);

// Write
void					write_log(t_philo_status status, t_philo *philo);

// Monitor
void					*health_monitor(void *data);

// Utils
void					error_exit(const char *error);
long					ft_atol(const char *str);
void					*ft_malloc(size_t bytes);
bool					dinner_finished(t_table *table);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_bool(t_mtx *mutex, bool *dest, bool value);
long					gettime(int time_code);
void					precise_usleep(long usec, t_table *table);
void					clean(t_table *table);

#endif