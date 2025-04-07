/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:23:52 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 14:23:52 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_action(int action, t_philo *philo)
{
	long	elapsed;

	elapsed = timestamp(philo->input) - (philo->input->time_start);
	safe_mutex(&philo->input->write_mutex, 0, philo->input);
	if (!get_status(&philo->input->data_mutex, &philo->input->end_program,
					philo->input))
	{
		if ((action == 4) || (action == 5)) 
			printf(Y"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		if (action == 0)
			printf(Y"%-6ld"RST" %d has died\n", elapsed, philo->id);
		if (action == 1)
			printf(Y"%-6ld"RST" %d has started eating\n", elapsed, philo->id);
		if (action == 2)
			printf(Y"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		if (action == 3)
			printf(Y"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
	}
	safe_mutex(&philo->input->write_mutex, 1, philo->input);
}

/* ACTION OPCODES

	DIED = 0
	EATING = 1
	SLEEPING = 2
	THINKING = 3
	TOOK_FIRST_FORK = 4
	TOOK_SECOND_FOR = 5

*/