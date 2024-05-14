/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:00:23 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/13 13:57:07 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		ft_mutex_handle(&philo->philo_mutex, INIT);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_flag = false;
	table->all_philos_ready = false;
	table->threads_running_nbr = 0;
	table->philos = ft_malloc(table->philo_nbr * sizeof(t_philo));
	table->forks = ft_malloc(table->philo_nbr * sizeof(t_fork));
	ft_mutex_handle(&table->write_mutex, INIT);
	ft_mutex_handle(&table->table_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		ft_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].id = i;
	}
	philo_init(table);
}
