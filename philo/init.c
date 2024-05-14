/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:25:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 18:54:37 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *nbr)
{
	int	i;

	i = -1;
	if (nbr[i] == '+' || nbr[i] == '-')
		i++;
	while (nbr[++i])
	{
		if (!(nbr[i] >= '0' && nbr[i] <= '9'))
			return (0);
	}
	return (1);
}

int	check_args(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if ((!(is_number(argv[i])) || (ft_atoi(argv[i]) <= 0))
			|| (ft_atoi(argv[i]) > 2147483647))
		{
			printf("Error\n");
			return (1);
		}
	}
	table->nbr_of_philos = ft_atoi(argv[1]);
	table->nbr_of_meals = 0;
	if (argv[5])
		table->nbr_of_meals = ft_atoi(argv[5]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->flag = 1;
	pthread_mutex_init(&table->w8, NULL);
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->eating, NULL);
	return (0);
}

static int	init_table(t_table *table)
{
	long long	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->nbr_of_philos);
	if (!table->philos)
		return (1);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->nbr_of_philos);
	if (!table->forks)
	{
		free(table->philos);
		return (1);
	}
	i = -1;
	while (++i < table->nbr_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			free(table->philos);
			free(table->forks);
			return (1);
		}
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	table->start_time = get_time();
	i = -1;
	while (++i < table->nbr_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = get_time();
		if (i % 2 == 0)
		{
			table->philos[i].left_hand = i;
			table->philos[i].right_hand = (i + 1) % table->nbr_of_philos;
		}
		else
		{
			table->philos[i].left_hand = (i + 1) % table->nbr_of_philos;
			table->philos[i].right_hand = i;
		}
		if (pthread_create(&table->philos[i].thread, NULL, &philo,
				&table->philos[i]))
			return (1);
	}
	return (0);
}

int	init_all(t_table *table)
{
	int	i;

	i = 0;
	if (init_table(table))
		i = 1;
	if (init_philos(table))
		i = 1;
	return (i);
}
