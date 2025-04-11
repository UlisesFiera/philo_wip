/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:21:53 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/04 17:21:53 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec_thread(int return_value, int opcode)
{
	if (!return_value)
		return (0);
	else
	{
		if (opcode == 0)
		{
			error_exit("Thread creation failure.");
		}
		if (opcode == 1)
		{
			error_exit("Thread joining failure.");
		}
		if (opcode == 2)
		{
			error_exit("Thread detach failure.");
		}
		return (1);
	}
}

int	safe_thread(pthread_t *thread, void *(*function)(void *),
					void *data, int opcode)
{
	if (opcode == 0)
	{
		if (exec_thread(pthread_create(thread,
			NULL, function, data), 0))
			return (1);
	}
	else if (opcode == 1)
	{
		if (exec_thread(pthread_join(*thread, NULL), 1))
			return (1);
	}
	else if (opcode == 2)
	{
		if (exec_thread(pthread_detach(*thread), 2))
			return (1);
	}
	return (0);
}

/* Thread opcode's

	CREATE = 0
	JOIN = 1
	DETACH = 2

*/

/* Notes

	Pointer to functions are usefull when you want to modify what the function
	does once the program is running. 

*/