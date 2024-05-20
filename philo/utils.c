/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:53:52 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/20 15:37:17 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	increase_long(t_mtx *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	++(*value);
	pthread_mutex_unlock(mutex);
}
