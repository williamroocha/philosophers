/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:10:46 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 09:36:47 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!dinner_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

// void	thinking(t_philo *philo, bool pre_simulation)
// {
// 	long	t_eat;
// 	long	t_sleep;
// 	long	t_think;

// 	if (!pre_simulation)
// 		write_status(THINKING, philo, DEBUG_MODE);
// 	if (philo->table->philo_nbr % 2 == 0)
// 		return ;
// 	t_eat = philo->table->time_to_eat;
// 	t_sleep = philo->table->time_to_sleep;
// 	t_think = (t_eat * 2) - t_sleep;
// 	if (t_think < 0)
// 		t_think = 0;
// 	precise_usleep(t_think * 0.42, philo->table);
// }

void	thinking(t_philo *philo, bool pre_simulation)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void	eat(t_philo *philo)
{
	ft_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	ft_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_nbr_max > 0
		&& philo->meals_count == philo->table->meals_nbr_max)
		set_bool(&philo->philo_mutex, &philo->full, true);
	ft_mutex_handle(&philo->first_fork->fork, UNLOCK);
	ft_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_for_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	// de_synchronize_philos(philo);
	while (!dinner_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->meals_nbr_max)
		return ;
	else if (1 == table->philo_nbr)
		ft_thread_handle(&table->philos[0].thread_id, lone_philo,
			&table->philos[0], CREATE);
	else
		while (++i < table->philo_nbr)
			ft_thread_handle(&table->philos[i].thread_id, dinner_routine,
				&table->philos[i], CREATE);
	ft_thread_handle(&table->monitor, health_monitor, table, CREATE);
	table->start_time = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_philos_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		ft_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_flag, true);
	ft_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
