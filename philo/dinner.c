/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:10:46 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/09 17:25:32 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	mutex_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILLISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_nbr_max > 0
		&& philo->meals_count == philo->table->meals_nbr_max)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->second_fork->fork, UNLOCK);
}

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}



static void	*dinner_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_for_all_philos(philo->table);
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

void	start_dinner(t_table *table)
{
	int	i;


	i = -1;
	if (table->meals_nbr_max == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		// todo
	}
	else
	{
		
		while (++i < table->philo_nbr)
		{
			thread_handler(&table->philos[i].thread_id, dinner_routine,
				&table->philos[i], CREATE);
			
		}
 	}
	table->start_time = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->end_flag, true);
	i = -1;
	while (++i < table->philo_nbr)
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
}
