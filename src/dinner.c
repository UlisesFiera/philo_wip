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
	set_long(&philo->philo_mutex, &philo->time_last_meal,
		timestamp(philo->input), philo->input);
	increase_long(&philo->input->data_mutex, &philo->input->nbr_threads_ready,
		philo->input);
	write_action(4, philo);
	printf("2ah\n");
	while (get_status(&philo->input->end_mutex, &philo->input->end_program,
			philo->input) == 0)
		precise_usleep(200);
	return (NULL);
}

void	actions(t_philo *philo)
{
	while ((get_status(&philo->input->end_mutex, &philo->input->end_program,
				philo->input)) == 0)
	{
		if (philo->full)
			return ;
		else
		{
			eat(philo);
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
	set_long(&philo->philo_mutex, &philo->time_last_meal,
		timestamp(input), input);
	increase_long(&philo->input->data_mutex, &philo->input->nbr_threads_ready,
		input);
	if (philo->id % 2)
		think(philo, 1);
	actions(philo);
	return (NULL);
}

void	thread_init(t_data *input)
{
	int		i;

	i = 0;
	if (input->nbr_max_meals == 0)
		return ;
	if (input->nbr_philo == 1)
	{
		safe_thread(&input->philos[0].philo_thread_id, one_philo,
			&input->philos[0], 0);
		set_status(&input->data_mutex, &input->all_threads_ready, 1, input);
	}
	else
	{
		while (i < input->nbr_philo)
		{
			if (safe_thread(&input->philos[i].philo_thread_id,
					dinner_simulation, &input->philos[i], 0))
				set_status(&input->end_mutex, &input->end_program, 1, input);
			i++;
		}
	}
	safe_thread(&input->monitor_dead, dead_philos, input, 0);
	set_status(&input->data_mutex, &input->all_threads_ready, 1, input);
}

void	dinner_start(t_data *input)
{
	int		i;

	thread_init(input);
	i = 0;
	while (i < input->nbr_philo)
	{
		if (safe_thread(&input->philos[i].philo_thread_id, NULL, NULL, 1))
			set_status(&input->end_mutex, &input->end_program, 1, input);
		input->philos[i].detached = 1;
		i++;
	}
	set_status(&input->data_mutex, &input->end_program, 1, input);
	safe_thread(&input->monitor_dead, NULL, NULL, 1);
	input->monitor_detached = 1;
}

/* ACTION OPCODES

	DIED = 0
	EATING = 1
	SLEEPING = 2
	THINKING = 3
	TOOK_FIRST_FORK = 4
	TOOK_SECOND_FOR = 5

*/
