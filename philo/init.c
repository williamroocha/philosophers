/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:25:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/14 18:42:24 by wiferrei         ###   ########.fr       */
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

int	check_args(t_geral *geral, char **argv)
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
	geral->nbr_of_philos = ft_atoi(argv[1]);
	geral->nbr_of_meals = 0;
	if (argv[5])
		geral->nbr_of_meals = ft_atoi(argv[5]);
	geral->time_to_die = ft_atoi(argv[2]);
	geral->time_to_eat = ft_atoi(argv[3]);
	geral->time_to_sleep = ft_atoi(argv[4]);
	geral->flag = 1;
	pthread_mutex_init(&geral->w8, NULL);
	pthread_mutex_init(&geral->write, NULL);
	pthread_mutex_init(&geral->eating, NULL);
	return (0);
}

static int	init_geral(t_geral *geral)
{
	long long	i;

	geral->philos = (t_philo *)malloc(sizeof(t_philo) * geral->nbr_of_philos);
	if (!geral->philos)
		return (1);
	geral->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* geral->nbr_of_philos);
	if (!geral->forks)
	{
		free(geral->philos);
		return (1);
	}
	i = -1;
	while (++i < geral->nbr_of_philos)
	{
		if (pthread_mutex_init(&geral->forks[i], NULL))
		{
			free(geral->philos);
			free(geral->forks);
			return (1);
		}
	}
	return (0);
}

static int	init_philos(t_geral *geral)
{
	int	i;

	geral->start_time = get_time();
	i = -1;
	while (++i < geral->nbr_of_philos)
	{
		geral->philos[i].id = i + 1;
		geral->philos[i].geral = geral;
		geral->philos[i].meals_eaten = 0;
		geral->philos[i].last_meal = get_time();
		if (i % 2 == 0)
		{
			geral->philos[i].left_hand = i;
			geral->philos[i].right_hand = (i + 1) % geral->nbr_of_philos;
		}
		else
		{
			geral->philos[i].left_hand = (i + 1) % geral->nbr_of_philos;
			geral->philos[i].right_hand = i;
		}
		if (pthread_create(&geral->philos[i].thread, NULL, &philo,
				&geral->philos[i]))
			return (1);
	}
	return (0);
}

int	init_all(t_geral *geral)
{
	int	i;

	i = 0;
	if (init_geral(geral))
		i = 1;
	if (init_philos(geral))
		i = 1;
	return (i);
}
