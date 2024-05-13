/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:25:10 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/09 16:56:43 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	mutex_handler(mutex, LOCK);
	ret = *value;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	mutex_handler(mutex, LOCK);
	ret = *value;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

bool	dinner_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_flag));
}
