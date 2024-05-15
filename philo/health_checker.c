/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:13:46 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/15 14:14:33 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop_flag(t_table *table)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&table->eating_mutex);
	if (table->stop_flag == 0)
		i = 0;
	pthread_mutex_unlock(&table->eating_mutex);
	return (i);
}

static void	check_eatean(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->wait_mutex);
	while (table->total_meals && i < table->philo_nbr
		&& table->philos[i].meals_consumed >= table->total_meals)
		i++;
	pthread_mutex_lock(&table->eating_mutex);
	if (i >= table->philo_nbr)
		table->stop_flag = 0;
	pthread_mutex_unlock(&table->eating_mutex);
	pthread_mutex_unlock(&table->wait_mutex);
}

static void	check_time_to_die(t_table *table)
{
	int		i;
	size_t	time;

	i = -1;
	while (++i < table->philo_nbr && check_stop_flag(table))
	{
		pthread_mutex_lock(&table->wait_mutex);
		time = get_time();
		if ((time - table->philos[i].last_meal_time) >= table->time_to_die)
		{
			print_message("died", &table->philos[i]);
			pthread_mutex_lock(&table->eating_mutex);
			table->stop_flag = 0;
			pthread_mutex_unlock(&table->eating_mutex);
		}
		pthread_mutex_unlock(&table->wait_mutex);
	}
}

void	check_health(t_table *table)
{
	while (check_stop_flag(table))
	{
		check_eatean(table);
		if (!check_stop_flag(table))
			break ;
		check_time_to_die(table);
	}
}
