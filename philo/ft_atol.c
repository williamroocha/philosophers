/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:45:15 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/18 17:45:46 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
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
		error_exit("Only positive numbers are allowed");
	if (!is_digit(*str))
		error_exit("Only int are allowed");
	number = str;
	while (is_digit(*str))
	{
		++str;
		++len;
	}
	if (*str != '\0' && !is_space(*str))
		error_exit("Invalid characters in input");
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("INT_MAX exceeded");
	return (num);
}
