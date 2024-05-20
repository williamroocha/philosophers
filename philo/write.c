/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:07:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/20 15:49:18 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	write_log(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_dinner;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	ft_mutex_handler(&philo->table->write_mutex, LOCK);
	if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		&& !dinner_finished(philo->table))
		printf("%-6ld" " %d has taken a fork\n", elapsed,
			philo->id);
	else if (status == EATING && !dinner_finished(philo->table))
		printf("%-6ld" " %d is eating\n", elapsed,
			philo->id);
	else if (status == SLEEPING && !dinner_finished(philo->table))
		printf("%-6ld" " %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !dinner_finished(philo->table))
		printf("%-6ld" " %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died\n", elapsed, philo->id);
	ft_mutex_handler(&philo->table->write_mutex, UNLOCK);
}
