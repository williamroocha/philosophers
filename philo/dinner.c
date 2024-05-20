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

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_log(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	write_log(TAKE_LEFT_FORK, philo);
	while (!dinner_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	ft_mutex_handler(&philo->left_fork->fork, LOCK);
	write_log(TAKE_LEFT_FORK, philo);
	ft_mutex_handler(&philo->right_fork->fork, LOCK);
	write_log(TAKE_RIGHT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_log(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	ft_mutex_handler(&philo->left_fork->fork, UNLOCK);
	ft_mutex_handler(&philo->right_fork->fork, UNLOCK);
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
		eat(philo);
		write_log(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->nbr_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		ft_thread_handler(&table->philos[0].thread_id, lone_philo,
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
