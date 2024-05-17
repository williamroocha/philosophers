/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:27:05 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/17 18:30:01 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->left_fork]);
	print_message("has taken a fork", philo);
}

void	lock_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->right_fork]);
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
	pthread_mutex_lock(&philo->table->wait_mutex);
	print_message("is eating", philo);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->table->wait_mutex);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->wait_mutex);
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->table->wait_mutex);
}
