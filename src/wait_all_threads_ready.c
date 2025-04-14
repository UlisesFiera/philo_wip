/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:40:28 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 12:40:28 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_all_threads_ready(t_data *input)
{
	int	ret_value;

	while ((ret_value = get_status(&input->data_mutex, &input->all_threads_ready)) == 0)
		precise_usleep(1000);
	if (ret_value == -1)
		return (1);
	return (0);
}

int	all_threads_running(t_mutex *mutex, long *threads, long nbr_philo, t_data *input)
{
	if (safe_mutex(mutex, 0))
	{
		if (set_status(&input->data_mutex, &input->end_program, 1))
		{
			printf("Exit on all_th failure\n");
			input->end_program = 1;
			return (1);
		}
	}
	if (*threads == nbr_philo)
	{
		if (safe_mutex(mutex, 1))
			if (set_status(&input->data_mutex, &input->end_program, 1))
			{
				printf("Exit on all_th failure\n");
				input->end_program = 1;
				return (1);
			}
		return (1);
	}
	if (safe_mutex(mutex, 1))
	{
		if (set_status(&input->data_mutex, &input->end_program, 1))
		{
			printf("Exit on all_th failure\n");
			input->end_program = 1;
			return (1);
		}
	}
	return (0);
}
