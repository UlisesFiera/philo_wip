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

void	exec_mutex(int return_value)
{
	if (return_value == 0)
		return ;
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
	}
}

void	safe_mutex(t_mutex *mutex, int opcode)
{
	if (opcode == 0)
		exec_mutex(pthread_mutex_lock(mutex));
	else if (opcode == 1)
		exec_mutex(pthread_mutex_unlock(mutex));
	else if (opcode == 2)
		exec_mutex(pthread_mutex_init(mutex, NULL));
	else if (opcode == 3)
		exec_mutex(pthread_mutex_destroy(mutex));
}

/* MUTEX opcode's

	LOCK = 0
	UNLOCK = 1
	INIT = 2
	DESTROY = 3

*/
