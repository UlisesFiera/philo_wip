/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:59:32 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/08 12:59:32 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philo_died(t_philo *philo)
{
	long	elapsed;
	long	last_meal;
	int		ret_value;

	if ((ret_value = get_status(&philo->philo_mutex, &philo->full)) == 1)
		return (0);
	last_meal = get_long(&philo->philo_mutex, &philo->time_last_meal);
	if (last_meal == -1)
		return (2);
	elapsed = timestamp() - last_meal;
	//printf("Philo %i elapsed %ld TTD %f\n", philo->id, elapsed, (philo->input->time_to_die / 1e3));
	if (elapsed > philo->input->time_to_die / 1e3)
		return (1);
	return (0);
}

void	*dead_philos(void *data)
{
	t_data	*input;
	int		ret_value;
	int		i;

	input = (t_data *)data;
	while (!all_threads_running(&input->data_mutex,
			&input->nbr_threads_ready, input->nbr_philo, input))
		;
	while ((ret_value = get_status(&input->data_mutex, &input->end_program)) == 0)
	{
		i = 0;
		while (i < input->nbr_philo)
		{
			if (philo_died(input->philos + i))
			{
				if (set_status(&input->data_mutex, &input->end_program, 1))
				{
					input->end_program = 1;
					return (NULL);
				}
				if (write_action(0, input->philos + i))
				{
					if (set_status(&input->data_mutex, &input->end_program, 1))
					{
						input->end_program = 1;
						return (NULL);
					}
				}
				return (NULL);
			}
			else if (philo_died(input->philos + i) == 2)
			{
				if (set_status(&input->data_mutex, &input->end_program, 1))
				{
					input->end_program = 1;
					return (NULL);
				}
				return (NULL);
			}
			i++;
		}
	}
	if (ret_value == -1)
	{
		if (set_status(&input->data_mutex, &input->end_program, 1))
		{
			input->end_program = 1;
			return (NULL);
		}
		return (NULL);
	}
	return (NULL);
}

/* Without the exit() function it comes to a point where finishing the program
   right when a mutex error happens its impossible, because we get into
   an infinite loop.*/