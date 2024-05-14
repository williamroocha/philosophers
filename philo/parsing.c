/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:37:12 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/13 14:00:15 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Feed me only positive values");
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("INT_MAX is the limit, not the sky");
	return (num);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	// if (table->philo_nbr > PHILO_MAX)
	// {
	// 	printf(RED"Max philos are %d\n"
	// 		G"make fclean and re-make with PHILO_MAX=nbr to change it\n"RST,
	// 		PHILO_MAX);
	// 	exit(EXIT_FAILURE);
	// }
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_sleep < 6e4
		|| table->time_to_eat < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (av[5])
		table->meals_nbr_max = ft_atol(av[5]);
	else
		table->meals_nbr_max = -1;
}
