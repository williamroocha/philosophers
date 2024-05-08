/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:54:49 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/08 15:25:23 by wiferrei         ###   ########.fr       */
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

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

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

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				meals_nbr_max;
	long				start_time;
	bool				end_flag;
	bool				all_philos_ready;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

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

void					parse_args(t_table *table, char **av);
void					data_init(t_table *table);
void					*my_malloc(size_t bytes);
static void				handle_thread_error(int status, t_opcode opcode);
void					mutex_handler(t_mtx *mtx, t_opcode opcode);
static void				handle_thread_error(int status, t_opcode opcode);
void					thread_handler(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode opcode);

// Dining manager
void					wait_for_all_philos(t_table *table);

// Getters and setters
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
long					get_long(t_mtx *mutex, long *value);
void					set_long(t_mtx *mutex, long *dest, long value);
bool					dinner_finished(t_table *table);

// Dinner utils
void					philo_error_exit(const char *msg);
long					get_time(t_time_code time_code);
void					precise_usleep(long usec, t_table *table);
void					write_status(t_philo_status status, t_philo *philo,
							bool debug);

#endif