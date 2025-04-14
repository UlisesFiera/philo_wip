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
	if (wait_all_threads_ready(philo->input))
		return (NULL);
	if (set_long(&philo->philo_mutex, &philo->time_last_meal, timestamp()))
		return (NULL);
	if (increase_long(&philo->input->data_mutex, &philo->input->nbr_threads_ready))
		return (NULL);
	if (write_action(4, philo))
		return (NULL);
	while (!get_status(&philo->input->data_mutex, &philo->input->end_program))
		precise_usleep(200);
	return (NULL);
}

void	actions(t_philo *philo)
{
	int		ret_value;

	while ((ret_value = get_status(&philo->input->data_mutex, &philo->input->end_program)) == 0)
	{
		if (philo->full)
			return ;
		else
		{
			ret_value = 0;
			while (get_status(&philo->philo_mutex, &philo->ready) == 0)
			{
				ret_value = get_status(&philo->philo_mutex, &philo->ready);
				if (ret_value == -1)
				{
					printf("Exit on actions failure\n");
					philo->input->end_program = 1;
					return ;
				}
			}
			//printf("Philo %i ready? %i\n", philo->id, philo->ready);
			if (eat(philo))
			{
				if (set_status(&philo->input->data_mutex, &philo->input->end_program, 1))
				{
					printf("Exit on actions failure\n");
					philo->input->end_program = 1;
					return ;
				}
				return ;
			}
			if (philo->full)
				return ;
			if (sleeping(philo))
			{
				if (set_status(&philo->input->data_mutex, &philo->input->end_program, 1))
				{
					printf("Exit on actions failure\n");
					philo->input->end_program = 1;
					return ;
				}
				return ;
			}
			if (think(philo))
			{
				if (set_status(&philo->input->data_mutex, &philo->input->end_program, 1))
				{
					printf("Exit on actions failure\n");
					philo->input->end_program = 1;
					return ;
				}
				return ;
			}
		}
	}
	if (ret_value == -1)
	{
		printf("Exit on actions failure\n");
		philo->input->end_program = 1;
		return ;
	}
	return ;
}

void	*dinner_simulation(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (wait_all_threads_ready(philo->input))
		return (NULL);
	if (set_long(&philo->philo_mutex, &philo->time_last_meal, timestamp()))
		return (NULL);
	if (increase_long(&philo->input->data_mutex, &philo->input->nbr_threads_ready))
		return (NULL);
	actions(philo);
	return (NULL);
}

void	dinner_start(t_data *input)
{
	int		i;

	i = 0;
	if (input->nbr_max_meals == 0)
		return ;
	else if (input->nbr_philo == 1)
	{
		if (safe_thread(&input->philos[0].philo_thread_id, one_philo, &input->philos[0], 0))
			return ;
	}
	else
	{
		while (i < input->nbr_philo)
		{
			if (safe_thread(&input->philos[i].philo_thread_id, dinner_simulation,
						&input->philos[i], 0))
						return ;
			i++;
		}
	}
	if (safe_thread(&input->monitor_dead, dead_philos, input, 0))
		return ;
	if (safe_thread(&input->monitor_prio, priority, input, 0))
		return ;
	if (set_status(&input->data_mutex, &input->all_threads_ready, 1))
		return ;
	i = 0;
	while (i < input->nbr_philo)
	{
		if (safe_thread(&input->philos[i].philo_thread_id, NULL, NULL, 1))
		{
			if (set_status(&input->data_mutex, &input->end_program, 1))
			{
				printf("Exit on dinner failure\n");
				input->end_program = 1;
				return ;
			}
			return ;
		}
		input->philos[i].detached = 1;
		i++;
	}
	if (set_status(&input->data_mutex, &input->end_program, 1))
		return ;
	printf("Exit on completion\n");
	safe_thread(&input->monitor_dead, NULL, NULL, 1);
	safe_thread(&input->monitor_prio, NULL, NULL, 1);
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