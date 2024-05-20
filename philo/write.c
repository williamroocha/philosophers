/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:07:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/20 15:34:57 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf(RED "%s\n" DEFAULT, error);
	exit(EXIT_FAILURE);
}

void	write_log(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_dinner;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	ft_mutex_handler(&philo->table->write_mutex, LOCK);
	if ((TAKE_LEFT_FORK == status || TAKE_RIGHT_FORK == status)
		&& !dinner_finished(philo->table))
		printf(WHITE "%-6ld" DEFAULT " %d has taken a fork\n", elapsed,
			philo->id);
	else if (EATING == status && !dinner_finished(philo->table))
		printf(WHITE "%-6ld" CYAN " %d is eating\n" DEFAULT, elapsed,
			philo->id);
	else if (SLEEPING == status && !dinner_finished(philo->table))
		printf(WHITE "%-6ld" DEFAULT " %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !dinner_finished(philo->table))
		printf(WHITE "%-6ld" DEFAULT " %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "%-6ld %d died\n" DEFAULT, elapsed, philo->id);
	ft_mutex_handler(&philo->table->write_mutex, UNLOCK);
}
