/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:58:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/19 20:11:23 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			"use MILLISECOND, MICROSECOND or SECONDS as input");
	return (18061995);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (dinner_finished(table))
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
