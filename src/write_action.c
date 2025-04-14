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
	long	current;

	safe_mutex(&philo->input->write_mutex, 0, philo->input);
	current = timestamp(philo->input);
	elapsed =  current - (philo->input->time_start);
	if (get_status(&philo->input->data_mutex, &philo->input->end_program, philo->input) == 0)
	{
		if ((action == 4)) 
			printf(Y"Elapsed (ms): %-6ld"RST" %d has one fork\n", elapsed, philo->id);
		if ((action == 5)) 
			printf(Y"Elapsed (ms): %-6ld"RST" %d has two forks\n", elapsed, philo->id);
		if (action == 1)
			printf(Y"Elapsed (ms): %-6ld"RST" %d has started eating\n", elapsed, philo->id);
		if (action == 2)
			printf(Y"Elapsed (ms): %-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		if (action == 3)
			printf(Y"Elapsed (ms): %-6ld"RST" %d is thinking\n", elapsed, philo->id);
	}
	if (action == 0)
		printf(Y"Elapsed (ms): %-6ld" R " %d has died\n" RST, elapsed, philo->id);
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