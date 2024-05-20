/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:23:53 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/20 15:23:55 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		ft_mutex_handler(&philo->philo_mutex, DESTROY);
	}
	ft_mutex_handler(&table->write_mutex, DESTROY);
	ft_mutex_handler(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
