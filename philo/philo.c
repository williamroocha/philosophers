/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:24:31 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/09 17:21:33 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_args(&table, av);
		data_init(&table);
		start_dinner(&table);
	}
	else
	{
		philo_error_exit("Invalid number of arguments");
	}
	return (0);
}
