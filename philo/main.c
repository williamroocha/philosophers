/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:20:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/15 13:28:16 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (verify_guest_list(&table, av) == -1)
			return (-1);
	}
	else
		error_exit("WRONG NUMBER OF ARGUMENTS\n");
	return (EXIT_SUCCESS);
}
