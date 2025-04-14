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
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = &forks[philo_position];
	fork2 = &forks[(philo_position + 1) % philo->input->nbr_philo];
	if (fork1 < fork2)
	{
		philo->first_fork = fork1;
		philo->second_fork = fork2;
	}
	else
	{
		philo->first_fork = fork2;
		philo->second_fork = fork1;
	}
}

int	philo_init(t_data *input)
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
		philo->detached = 0;
		philo->input = input;
		safe_mutex(&philo->philo_mutex, 2, input);
		assign_forks(philo, input->forks, i);
		i++;
	}
	return (0);
}

void	mutex_init(t_data *input)
{
	safe_mutex(&input->data_mutex, 2, input);
	safe_mutex(&input->write_mutex, 2, input);
	safe_mutex(&input->end_mutex, 2, input);
}

int	data_init(t_data *input)
{
	int	i;

	input->end_program = 0;
	input->all_threads_ready = 0;
	input->nbr_threads_ready = 0;
	input->monitor_detached = 0;
	input->philos = safe_malloc(sizeof(t_philo) * input->nbr_philo);
	input->forks = safe_malloc(sizeof(t_fork) * input->nbr_philo);
	if (!input->philos || !input->forks)
		return (1);
	input->time_start = timestamp(input);
	mutex_init(input);
	i = 0;
	while (i < input->nbr_philo)
	{
		safe_mutex(&input->forks[i].fork_mutex, 2, input);
		safe_mutex(&input->forks[i].use_mutex, 2, input);
		input->forks[i].fork_id = i;
		input->forks[i].fork_in_use = 0;
		i++;
	}
	if (philo_init(input))
		return (1);
	return (0);
}
