/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:55:05 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/19 18:49:38 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_limits(t_table *table)
{
	if (table->philo_nbr > PHILO_MAX)
	{
		printf(RED "The number of philosophers is too big, "
			"the limit is %d.\n" DEFAULT,
			PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	if (table->time_to_die < 6e4 || table->time_to_sleep < 6e4
		|| table->time_to_eat < 6e4)
		error_exit("The time is too short, the minimum is 60ms");
}

static void	parse_args(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}

void	parse(t_table *table, char **av)
{
	parse_args(table, av);
	check_limits(table);
}
