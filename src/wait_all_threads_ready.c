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

void	wait_all_threads_ready(t_data *input)
{
	while (get_status(&input->data_mutex,
			&input->all_threads_ready, input) == 0
		&& get_status(&input->end_mutex, &input->end_program, input) == 0)
		precise_usleep(1000);
}

int	all_threads_running(t_mutex *mutex, long *threads, long nbr_philo,
	t_data *input)
{
	while (get_status(&input->end_mutex, &input->end_program, input) == 0)
	{
		safe_mutex(mutex, 0, input);
		if (*threads == nbr_philo)
		{
			safe_mutex(mutex, 1, input);
			return (1);
		}
		safe_mutex(mutex, 1, input);
	}
	return (0);
}
