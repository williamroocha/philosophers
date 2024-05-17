/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:22:41 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/17 18:42:06 by wiferrei         ###   ########.fr       */
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

int	check_args(t_table *table, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if ((!(is_number(av[i])) || (ft_atoi(av[i]) <= 0))
			|| (ft_atoi(av[i]) > 2147483647))
		{
			error_exit("WRONG ARGUMENTS\n");
		}
	}
	table->philo_nbr = ft_atoi(av[1]);
	table->total_meals = 0;
	if (av[5])
		table->total_meals = ft_atoi(av[5]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->stop_flag = 1;
	pthread_mutex_init(&table->wait_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->eating_mutex, NULL);
	return (0);
}

void	*dinner_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->philo_nbr == 1)
	{
		print_message("has taken a fork", philo);
		ft_usleep(philo->table->time_to_die);
	}
	while (check_stop_flag(philo->table))
	{
		if (philo->id % 2)
			ft_usleep(100);
		else
			precise_usleep(philo->table->time_to_die, philo->table);
		if (philo->table->total_meals > 0
			&& philo->meals_consumed >= philo->table->total_meals)
			break ;
		eat(philo);
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->right_fork]);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

int	verify_guest_list(t_table *table, char **av)
{
	if (check_args(table, av))
		return (-1);
	if (organize_all(table))
		return (-1);
	check_health(table);
	cleanup_the_mess(table);
	return (0);
}
