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

void	exec_thread(int return_value, t_data *input)
{
	if (!return_value)
		return ;
	else
		error_exit("Thread failure.", input);
}

void	safe_thread(pthread_t *philo_thread_id, void *(*function)(void *),
					t_philo *philos, int opcode, t_data *input)
{
	if (opcode == 0)
		exec_thread(pthread_create(philo_thread_id, NULL, function, philos), input);
	else if (opcode == 1)
		exec_thread(pthread_join(*philo_thread_id, NULL), input);
	else if (opcode == 2)
		exec_thread(pthread_detach(*philo_thread_id), input);
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