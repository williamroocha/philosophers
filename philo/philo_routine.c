/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:27:05 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 18:55:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_hand]);
	print_message("has taken a fork", philo);
}

void	lock_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->right_hand]);
	print_message("has taken a fork", philo);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	sleep_philo(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->table->time_to_sleep);
}

void	eat(t_philo *philo)
{
	lock_right_fork(philo);
	lock_left_fork(philo);
	pthread_mutex_lock(&philo->table->w8);
	print_message("is eating", philo);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->w8);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->w8);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->w8);
}
