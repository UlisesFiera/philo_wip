/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:52:22 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/04 16:52:22 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fail_mutex(int return_value, t_data *input)
{
	if (return_value == 0)
		return (0);
	else
	{
		if (return_value == 22)
			error_exit("Invalid mutex or invalid attributes.");
		if (return_value == 16)
			error_exit("Mutex is already locked.");
		if (return_value == 11)
			error_exit("Maximum recursion limit exceeded.");
		if (return_value == 35)
			error_exit("Deadlock situation detected.");
		if (return_value == 1)
			error_exit("Insufficient permissions.");
		if (return_value == 12)
			error_exit("Insufficient memory to initialize mutex.");
		if (return_value == 4)
			error_exit("Interrupted by a signal.");
		input->end_program = 1;
		return (1);
	}
}

int	safe_mutex(t_mutex *mutex, int opcode, t_data *input)
{
	if (opcode == 0)
	{
		if (fail_mutex(pthread_mutex_lock(mutex), input))
			return (1);
	}
	else if (opcode == 1)
	{
		if (fail_mutex(pthread_mutex_unlock(mutex), input))
			return (1);
	}
	else if (opcode == 2)
	{
		if (fail_mutex(pthread_mutex_init(mutex, NULL), input))
			return (1);
	}
	else if (opcode == 3)
	{
		if (fail_mutex(pthread_mutex_destroy(mutex), input))
			return (1);
	}
	return (0);
}

/* MUTEX opcode's

	LOCK = 0
	UNLOCK = 1
	INIT = 2
	DESTROY = 3

*/
