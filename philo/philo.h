/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:54:49 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/13 10:35:11 by wiferrei         ###   ########.fr       */
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

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

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
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef struct s_fork
{
	t_mtx				fork;
	int					id;
}						t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	bool				full;
	long				meals_count;
	long				last_meal;
	pthread_t			thread_id;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_nbr_max;
	long				start_time;
	bool				end_flag;
	bool				all_philos_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
};

/*********************************************************/
# define RST "\033[0m" /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m" /* Bold Green */
# define Y "\033[1;33m" /* Bold Yellow */
# define B "\033[1;34m" /* Bold Blue */
# define M "\033[1;35m" /* Bold Magenta */
# define C "\033[1;36m" /* Bold Cyan */
# define W "\033[1;37m" /* Bold White */
/*********************************************************/

// Dinner

// Dining manager

// Getters and setters

// Dinner utils

// General utils
void					ft_malloc(size_t bytes);
void					error_exit(const char *error);
static void				handle_mutex_error(int status, t_opcode opcode);
static void				handle_thread_error(int status, t_opcode opcode);
void					ft_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					ft_thread_handle(pthread_t *thread,
							void *(*foo)(void *), void *data, t_opcode opcode);
long					gettime(int time_code);
void					precise_usleep(long usec, t_table *table);
void					clean(t_table *table);
void					write_status(t_philo_status status, t_philo *philo,
							bool debug);
static void				assign_forks(t_philo *philo, t_fork *forks,
							int philo_position);
static void				philo_init(t_table *table);
void					data_init(t_table *table);

// Parsing
void					parse_input(t_table *table, char **av);
static long				ft_atol(const char *str);
static const char		*valid_input(const char *str);
static inline bool		is_space(char c);
static inline bool		is_digit(char c);

#endif