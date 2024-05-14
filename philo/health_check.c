/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:26:40 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 09:34:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*health_monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_philos_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!dinner_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !dinner_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_flag, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}