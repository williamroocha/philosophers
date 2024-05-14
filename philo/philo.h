/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:22:13 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 18:49:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*********************************************************/
# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */
/*********************************************************/

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int					left_hand;
	int					right_hand;

	int					id;
	int					meals_eaten;

	size_t				last_meal;

	pthread_t			thread;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					nbr_of_philos;
	int					nbr_of_meals;
	int					flag;

	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;

	t_mutex				write;
	t_mutex				w8;
	t_mutex				eating;
	t_mutex				*forks;

	t_philo				*philos;
}						t_table;

void					*philo(void *arg);

int						check_args(t_table *table, char **argv);
int						init_all(t_table *table);

long					ft_atoi(char *str);
size_t					get_time(void);
void					destroy_all(t_table *table);
void					print_message(char *str, t_philo *philo);
void					ft_usleep(size_t time);

void					lock_left_fork(t_philo *philo);
void					lock_right_fork(t_philo *philo);
void					think(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					eat(t_philo *philo);

int						check_flag(t_table *table);
void					check_dead(t_table *table);

#endif