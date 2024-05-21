/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:14:47 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/20 15:30:41 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lonely_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_log(TAKE_LEFT_FORK, philo);
	while (!dinner_finished(philo->table))
		ft_usleep(200, philo->table);
	return (NULL);
}

static void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	while (!dinner_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		philo_routine(philo);
	}
	return (NULL);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		ft_thread_handler(&table->philos[0].thread_id, lonely_philo,
			&table->philos[0], CREATE);
	else
		while (++i < table->philo_nbr)
			ft_thread_handler(&table->philos[i].thread_id, dinner_routine,
				&table->philos[i], CREATE);
	ft_thread_handler(&table->monitor, health_monitor, table, CREATE);
	table->start_dinner = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_philos_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		ft_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_dinner, true);
	ft_thread_handler(&table->monitor, NULL, NULL, JOIN);
}
