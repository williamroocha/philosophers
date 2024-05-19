/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:53:52 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/19 17:14:52 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf(RED "%s\n" DEFAULT, error);
	exit(EXIT_FAILURE);
}

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	ft_mutex_handler(mutex, LOCK);
	*dest = value;
	ft_mutex_handler(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	ft_mutex_handler(mutex, LOCK);
	ret = *value;
	ft_mutex_handler(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	ft_mutex_handler(mutex, LOCK);
	ret = *value;
	ft_mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	ft_mutex_handler(mutex, LOCK);
	*dest = value;
	ft_mutex_handler(mutex, UNLOCK);
}

long	gettime(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		error_exit("Wrong input to gettime:"
					"use <MILLISECOND> <MICROSECOND> <SECONDS>");
	return (1337);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (gettime(MICROSECOND) - start < usec)
				;
	}
}

// sync

void	wait_all_philos(t_table *table)
{
	bool	all_philos_ready;

	while (true)
	{
		all_philos_ready = get_bool(&table->table_mutex,
				&table->all_philos_ready);
		if (all_philos_ready)
			break ;
	}
}

void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	++(*value);
	pthread_mutex_unlock(mutex);
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	ft_mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	ft_mutex_handler(mutex, UNLOCK);
	return (ret);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_dinner));
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		ft_mutex_handler(&philo->philo_mutex, DESTROY);
	}
	ft_mutex_handler(&table->write_mutex, DESTROY);
	ft_mutex_handler(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}