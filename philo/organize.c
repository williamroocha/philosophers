/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:31:33 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/17 18:27:28 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	organize_table(t_table *table)
{
	long long	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (1);
	table->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->philo_nbr);
	if (!table->forks_mutex)
	{
		free(table->philos);
		return (1);
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks_mutex[i], NULL))
		{
			free(table->philos);
			free(table->forks_mutex);
			return (1);
		}
	}
	return (0);
}

static int	sit_the_philos(t_table *table)
{
	int	i;

	table->start_time = get_time();
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_consumed = 0;
		table->philos[i].last_meal_time = get_time();
		if (i % 2 == 0)
		{
			table->philos[i].left_fork = i;
			table->philos[i].right_fork = (i + 1) % table->philo_nbr;
		}
		else
		{
			table->philos[i].left_fork = (i + 1) % table->philo_nbr;
			table->philos[i].right_fork = i;
		}
		if (pthread_create(&table->philos[i].philo_thread, NULL,
				&dinner_routine, &table->philos[i]))
			return (1);
	}
	return (0);
}

int	organize_all(t_table *table)
{
	int	i;

	i = 0;
	if (organize_table(table))
		i = 1;
	if (sit_the_philos(table))
		i = 1;
	return (i);
}
