/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:42:53 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/03 10:42:53 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			input;

	if (argc == 5 || argc == 6)
	{
		if (parse_input(&input, argv))
			return (1);
		if (data_init(&input))
		{
			free_all(&input);
			return (1);
		}
		dinner_start(&input);
		free_all(&input);
	}
	else
	{
		error_exit("Incorrect input\n"
			Y "Use: <./philo nbr0 nbr1 nbr2 nbr3 [nbr4]" RST);
	}
	return (0);
}
