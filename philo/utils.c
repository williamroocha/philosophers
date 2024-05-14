/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:24:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 18:40:00 by wiferrei         ###   ########.fr       */
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

void	destroy_all(t_geral *geral)
{
	int	i;

	i = -1;
	while (++i < geral->nbr_of_philos)
		pthread_join(geral->philos[i].thread, 0);
	i = -1;
	while (++i < geral->nbr_of_philos)
		pthread_mutex_destroy(&geral->forks[i]);
	pthread_mutex_destroy(&geral->w8);
	pthread_mutex_destroy(&geral->write);
	pthread_mutex_destroy(&geral->eating);
	free(geral->forks);
	free(geral->philos);
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

	if (!check_flag(philo->geral))
		return ;
	pthread_mutex_lock(&philo->geral->write);
	time = get_time();
	printf("%zu %d %s\n", time - philo->geral->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->geral->write);
}

int	check_flag(t_geral *geral)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&geral->eating);
	if (geral->flag == 0)
		i = 0;
	pthread_mutex_unlock(&geral->eating);
	return (i);
}

static void	check_eatean(t_geral *geral)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&geral->w8);
	while (geral->nbr_of_meals && i < geral->nbr_of_philos
		&& geral->philos[i].meals_eaten >= geral->nbr_of_meals)
		i++;
	pthread_mutex_lock(&geral->eating);
	if (i >= geral->nbr_of_philos)
		geral->flag = 0;
	pthread_mutex_unlock(&geral->eating);
	pthread_mutex_unlock(&geral->w8);
}

static void	check_time_to_die(t_geral *geral)
{
	int		i;
	size_t	time;

	i = -1;
	while (++i < geral->nbr_of_philos && check_flag(geral))
	{
		pthread_mutex_lock(&geral->w8);
		time = get_time();
		if ((time - geral->philos[i].last_meal) >= geral->time_to_die)
		{
			print_message("died", &geral->philos[i]);
			pthread_mutex_lock(&geral->eating);
			geral->flag = 0;
			pthread_mutex_unlock(&geral->eating);
		}
		pthread_mutex_unlock(&geral->w8);
	}
}

void	check_dead(t_geral *geral)
{
	while (check_flag(geral))
	{
		check_eatean(geral);
		if (!check_flag(geral))
			break ;
		check_time_to_die(geral);
	}
}