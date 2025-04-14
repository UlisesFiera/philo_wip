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

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads_ready(philo->input);
	set_long(&philo->philo_mutex, &philo->time_last_meal, timestamp(philo->input), philo->input);
	increase_long(&philo->input->data_mutex, &philo->input->nbr_threads_ready, philo->input);
	write_action(4, philo);
	while (get_status(&philo->input->end_mutex, &philo->input->end_program, philo->input) == 0)
		precise_usleep(200);
	return (NULL);
}

void	actions(t_philo *philo)
{
	while ((get_status(&philo->input->end_mutex, &philo->input->end_program, philo->input)) == 0)
	{
		//int	i;
		if (philo->full)
			return ;
		else
		{
			/*
			while ((get_status(&philo->philo_mutex, &philo->ready, philo->input) == 0))
			{
				if (get_status(&philo->input->end_mutex, &philo->input->end_program, philo->input) == 1)
					return ;
				get_status(&philo->philo_mutex, &philo->ready, philo->input);
			}
			*/
			eat(philo);
			/*
			if (get_status(&philo->philo_mutex, &philo->ready, philo->input) == 2)
			{
				i = 0;
				while (i < philo->input->nbr_philo)
				{
					set_status(&philo->input->philos[i].philo_mutex, &philo->input->philos[i].ready, 1, philo->input);
					i++;
				}
			}
			*/
			if (philo->full)
				return ;
			sleeping(philo);
			think(philo, 0);
		}
	}
	return ;
}

void	*dinner_simulation(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	wait_all_threads_ready(philo->input);
	set_long(&philo->philo_mutex, &philo->time_last_meal, timestamp(input), input);
	increase_long(&philo->input->data_mutex, &philo->input->nbr_threads_ready, input);
	if (philo->id % 2)
		think(philo, 1);
	actions(philo);
	return (NULL);
}

void	dinner_start(t_data *input)
{
	int		i;

	i = 0;
	if (input->nbr_max_meals == 0)
		return ;
	if (input->nbr_philo == 1)
		safe_thread(&input->philos[0].philo_thread_id, one_philo, &input->philos[0], 0, input);
	else
	{
		while (i < input->nbr_philo)
		{
			safe_thread(&input->philos[i].philo_thread_id, dinner_simulation,
						&input->philos[i], 0, input);
			i++;
		}
	}
	safe_thread(&input->monitor_dead, dead_philos, input, 0, input);
	//safe_thread(&input->monitor_prio, priority, input, 0, input);
	set_status(&input->data_mutex, &input->all_threads_ready, 1, input);
	i = 0;
	while (i < input->nbr_philo)
	{
		safe_thread(&input->philos[i].philo_thread_id, NULL, NULL, 1, input);
		input->philos[i].detached = 1;
		i++;
	}
	set_status(&input->data_mutex, &input->end_program, 1, input);
	printf("Exit on completion\n");
	safe_thread(&input->monitor_dead, NULL, NULL, 1, input);
	//safe_thread(&input->monitor_prio, NULL, NULL, 1, input);
	input->monitor_detached = 1;
	return ;
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

	If a mutex fails, I just change the general error flag to 1 without mutex.
	Even though is a race condition, it doesn't matter because it only happens on
	failure, and the theoretical possibility that the 0 to 1 writting gets
	corrupted is totally remote.

*/