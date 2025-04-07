/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:05:19 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 09:05:19 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	actions(t_philo *philo)
{
	while (!get_status(&philo->input->data_mutex, &philo->input->end_program))
	{
		if (philo->full)
			return ;
		else
		{
			eat(philo);
			sleeping(philo);
			think(philo);
		}
	}
}

void	*dinner_simulation(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	wait_all_threads_ready(philo->input);
	actions(philo);
	return (NULL);
}

void	dinner_start(t_data *input)
{
	int	i;

	i = 0;
	if (input->nbr_max_meals == 0)
		return ;
	else
	{
		while (i < input->nbr_philo)
		{
			safe_thread(&input->philos[i].philo_thread_id, dinner_simulation,
						&input->philos[i], 0);
			i++;
		}
	}
	set_status(&input->data_mutex, &input->all_threads_ready, 1);
	i = 0;
	while (i < input->nbr_philo)
	{
		safe_thread(&input->philos[i].philo_thread_id, NULL, NULL, 1);
		i++;
	}
}

/* ACTION OPCODES

	DIED = 0
	EATING = 1
	SLEEPING = 2
	THINKING = 3
	TOOK_FIRST_FORK = 4
	TOOK_SECOND_FOR = 5

*/

/* NOTES

	The main function acts just like any other thread, so it will keep 
	moving forward in it's execution. This means for example that wait_for_threads
	and set_status will both be executed, so the spinlock will break because
	eventually set_status will set all threads (philo) as true (1).

*/