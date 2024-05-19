/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:43:26 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/19 17:10:22 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse(&table, av);
		init(&table);
		dinner(&table);
		clean(&table);
	}
	else
		error_exit("Invalid number of arguments");
	return (EXIT_SUCCESS);
}
