/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-21 12:55:17 by wiferrei          #+#    #+#             */
/*   Updated: 2024-05-21 12:55:17 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	write_log(THINKING, philo);
}

static void	philo_sleep(t_philo *philo)
{
	write_log(SLEEPING, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

static void	philo_eat(t_philo *philo)
{
	ft_mutex_handler(&philo->left_fork->fork, LOCK);
	write_log(TAKE_LEFT_FORK, philo);
	ft_mutex_handler(&philo->right_fork->fork, LOCK);
	write_log(TAKE_RIGHT_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_log(EATING, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	ft_mutex_handler(&philo->left_fork->fork, UNLOCK);
	ft_mutex_handler(&philo->right_fork->fork, UNLOCK);
}

void	philo_routine(t_philo *philo)
{
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
}
