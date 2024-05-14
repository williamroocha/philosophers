/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:24:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 19:02:44 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	long	i;
	long	res;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	destroy_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nbr_of_philos)
		pthread_join(table->philos[i].thread, 0);
	i = -1;
	while (++i < table->nbr_of_philos)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->w8);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->eating);
	free(table->forks);
	free(table->philos);
}

void	ft_usleep(size_t time)
{
	size_t	st;

	st = get_time();
	while ((get_time() - st) < time)
	{
		usleep(time / 10);
	}
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	if (!check_flag(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->write);
	time = get_time();
	printf("%zu %d %s\n", time - philo->table->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->table->write);
}

int	check_flag(t_table *table)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&table->eating);
	if (table->flag == 0)
		i = 0;
	pthread_mutex_unlock(&table->eating);
	return (i);
}

static void	check_eatean(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->w8);
	while (table->nbr_of_meals && i < table->nbr_of_philos
		&& table->philos[i].meals_consumed >= table->nbr_of_meals)
		i++;
	pthread_mutex_lock(&table->eating);
	if (i >= table->nbr_of_philos)
		table->flag = 0;
	pthread_mutex_unlock(&table->eating);
	pthread_mutex_unlock(&table->w8);
}

static void	check_time_to_die(t_table *table)
{
	int		i;
	size_t	time;

	i = -1;
	while (++i < table->nbr_of_philos && check_flag(table))
	{
		pthread_mutex_lock(&table->w8);
		time = get_time();
		if ((time - table->philos[i].last_meal_time) >= table->time_to_die)
		{
			print_message("died", &table->philos[i]);
			pthread_mutex_lock(&table->eating);
			table->flag = 0;
			pthread_mutex_unlock(&table->eating);
		}
		pthread_mutex_unlock(&table->w8);
	}
}

void	check_dead(t_table *table)
{
	while (check_flag(table))
	{
		check_eatean(table);
		if (!check_flag(table))
			break ;
		check_time_to_die(table);
	}
}