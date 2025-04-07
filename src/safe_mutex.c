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

void	exec_mutex(int return_value, t_data *input)
{
	if (!return_value)
		return ;
	else
		error_exit("Mutex failure.", input);
}

void	safe_mutex(t_mutex *mutex, int opcode, t_data *input)
{
	if (opcode == 0)
		exec_mutex(pthread_mutex_lock(mutex), input);
	else if (opcode == 1)
		exec_mutex(pthread_mutex_unlock(mutex), input);
	else if (opcode == 2)
		exec_mutex(pthread_mutex_init(mutex, NULL), input);
	else if (opcode == 3)
		exec_mutex(pthread_mutex_destroy(mutex), input);
}

/* MUTEX opcode's

	LOCK = 0
	UNLOCK = 1
	INIT = 2
	DESTROY = 3

*/
