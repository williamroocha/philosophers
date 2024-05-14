/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:26:33 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/13 14:07:51 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf(RED "%s\n" RST, error);
	exit(EXIT_FAILURE);
}

long	gettime(int time_code)
{
	struct timeval	tv;

	if (0 != gettimeofday(&tv, NULL))
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
	while (usec > gettime(MICROSECOND) - start)
	{
		if (dinner_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (1e4 < rem)
			usleep(rem / 2);
		else
			while (usec > gettime(MICROSECOND) - start)
				;
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		ft_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	ft_mutex_handle(&table->write_mutex, DESTROY);
	ft_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (TAKE_FIRST_FORK == status && !dinner_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 1° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->first_fork->id);
	else if (TAKE_SECOND_FORK == status && !dinner_finished(philo->table))
		printf(W"%6ld"RST" %d has taken the 2° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->second_fork->id);
	else if (EATING == status && !dinner_finished(philo->table))
		printf(W"%6ld"C" %d is eating 🍝"
			"\t\t\t"Y"[🍝 %ld 🍝]\n"RST, elapsed, philo->id, philo->meals_count);
	else if (SLEEPING == status && !dinner_finished(philo->table))
		printf(W"%6ld"RST" %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !dinner_finished(philo->table))
		printf(W"%6ld"RST" %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t💀💀💀 %6ld %d died   💀💀💀\n"RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_time;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	ft_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !dinner_finished(philo->table))
			printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !dinner_finished(philo->table))
			printf(W "%-6ld" C " %d is eating\n" RST, elapsed, philo->id);
		else if (status == SLEEPING && !dinner_finished(philo->table))
			printf(W "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !dinner_finished(philo->table))
			printf(W "%-6ld" RST " %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf(RED "%-6ld %d died\n" RST, elapsed, philo->id);
	}
	ft_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
