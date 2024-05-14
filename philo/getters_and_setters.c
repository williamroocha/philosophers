/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:25:10 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/13 13:54:05 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	ft_mutex_handle(mutex, LOCK);
	*dest = value;
	ft_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	ft_mutex_handle(mutex, LOCK);
	ret = *value;
	ft_mutex_handle(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	ft_mutex_handle(mutex, LOCK);
	ret = *value;
	ft_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	ft_mutex_handle(mutex, LOCK);
	*dest = value;
	ft_mutex_handle(mutex, UNLOCK);
}

bool	dinner_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_flag));
}
