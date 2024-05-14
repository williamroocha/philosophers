/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:41:11 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 09:33:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_all_philos(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_philos_ready))
		;
}

void	increase_long(t_mtx *mutex, long *value)
{
	ft_mutex_handle(mutex, LOCK);
	(*value)++;
	ft_mutex_handle(mutex, UNLOCK);
}

bool	all_philos_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	ft_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	ft_mutex_handle(mutex, UNLOCK);
	return (ret);
}
