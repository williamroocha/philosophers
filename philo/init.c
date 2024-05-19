/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:48:31 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/19 19:06:33 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->left_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->right_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[philo_position];
		philo->right_fork = &forks[(philo_position + 1) % philo_nbr];
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
		philo->meals_counter = 0;
		philo->table = table;
		ft_mutex_handler(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

static void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_dinner = false;
	table->all_philos_ready = false;
	table->threads_running_nbr = 0;
	table->forks = ft_malloc(sizeof(t_fork) * table->philo_nbr);
	table->philos = ft_malloc(sizeof(t_philo) * table->philo_nbr);
	ft_mutex_handler(&table->write_mutex, INIT);
	ft_mutex_handler(&table->table_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		ft_mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
}

void	init(t_table *table)
{
	data_init(table);
	philo_init(table);
}
