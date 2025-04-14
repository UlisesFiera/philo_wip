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

int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	last_meal;

	if (get_status(&philo->philo_mutex, &philo->full, philo->input) == 1)
		return (0);
	last_meal = get_long(&philo->philo_mutex, &philo->time_last_meal,
			philo->input);
	elapsed = timestamp(philo->input) - last_meal;
	if (elapsed >= philo->input->time_to_die / 1e3 + 10)
		return (1);
	return (0);
}

void	*dead_philos(void *data)
{
	t_data	*input;
	int		philo_status;
	int		i;

	input = (t_data *)data;
	while (!all_threads_running(&input->data_mutex,
			&input->nbr_threads_ready, input->nbr_philo, input))
		;
	while (get_status(&input->end_mutex, &input->end_program, input) == 0)
	{
		i = 0;
		while (i < input->nbr_philo)
		{
			philo_status = philo_died(input->philos + i);
			if (philo_status == 1)
			{
				write_action(0, input->philos + i);
				set_status(&input->end_mutex, &input->end_program, 1, input);
				return (NULL);
			}
			i++;
		}
		precise_usleep(10);
	}
	return (NULL);
}

/* Without the exit() function it comes to a point where finishing the program
   right when a mutex error happens its impossible, because we get into
   an infinite loop.*/