/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:43:47 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/04 11:43:47 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	nbr_philo;

	nbr_philo = philo->input->nbr_philo;

	philo->first_fork = &forks[(philo_position + 1) % nbr_philo];  
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % nbr_philo];
	}

}

void	philo_init(t_data *input)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < input->nbr_philo)
	{
		philo = input->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meal_count = 0;
		philo->input = input;
		safe_mutex(&philo->philo_mutex, 2);
		assign_forks(philo, input->forks, i);
		i++;
	}
}

int	data_init(t_data *input)
{
	int	i;

	input->end_program = 0;
	input->all_threads_ready = 0;
	input->philos = safe_malloc(sizeof(t_philo) * input->nbr_philo);
	input->time_start = timestamp();
	safe_mutex(&input->data_mutex, 2);
	safe_mutex(&input->write_mutex, 2);
	input->forks = safe_malloc(sizeof(t_fork) * input->nbr_philo);
	i = 0;
	while (i < input->nbr_philo)
	{
		safe_mutex(&input->forks[i].fork_mutex, 2);
		input->forks[i].fork_id = i;
		i++;
	}
	philo_init(input);
	return (0);
}
