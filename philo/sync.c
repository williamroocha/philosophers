/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:58:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/21 15:53:50 by wiferrei         ###   ########.fr       */
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

