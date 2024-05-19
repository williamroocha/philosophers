/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:07:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/19 17:19:34 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_log(t_philo_status status, t_philo *philo)
{
	long elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_dinner;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	ft_mutex_handler(&philo->table->write_mutex, LOCK);

	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !simulation_finished(philo->table))
		printf(WHITE "%-6ld" DEFAULT " %d has taken a fork\n", elapsed,
			philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(WHITE "%-6ld" CYAN " %d is eating\n" DEFAULT, elapsed,
			philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(WHITE "%-6ld" DEFAULT " %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(WHITE "%-6ld" DEFAULT " %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "%-6ld %d died\n" DEFAULT, elapsed, philo->id);

	ft_mutex_handler(&philo->table->write_mutex, UNLOCK);
}