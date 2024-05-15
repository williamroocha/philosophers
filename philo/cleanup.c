/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:07:46 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/15 14:08:17 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_the_mess(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].philo_thread, 0);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&table->forks_mutex[i]);
	pthread_mutex_destroy(&table->wait_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->eating_mutex);
	free(table->forks_mutex);
	free(table->philos);
}
