/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:20:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 19:14:38 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *arg)
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
			usleep(100);
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

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc >= 5 && argc <= 6)
	{
		if (check_args(&table, argv))
			return (-1);
		if (init_all(&table))
			return (-1);
		check_dead(&table);
		destroy_all(&table);
	}
	return (0);
}
