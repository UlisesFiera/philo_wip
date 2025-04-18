/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:57:35 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/06 09:57:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_routine(t_philo *philo)
{
	philo->first_fork->fork_in_use = 1;
	philo->second_fork->fork_in_use = 1;
	safe_mutex(&philo->first_fork->fork_mutex, 0, philo->input);
	write_action(4, philo);
	safe_mutex(&philo->second_fork->fork_mutex, 0, philo->input);
	write_action(5, philo);
	set_long(&philo->philo_mutex, &philo->time_last_meal,
		timestamp(philo->input), philo->input);
	philo->meal_count++;
	write_action(1, philo);
	precise_usleep(philo->input->time_to_eat);
	if (philo->input->nbr_max_meals > 0
		&& philo->meal_count == philo->input->nbr_max_meals)
		set_status(&philo->philo_mutex, &philo->full, 1, philo->input);
	safe_mutex(&philo->first_fork->fork_mutex, 1, philo->input);
	safe_mutex(&philo->second_fork->fork_mutex, 1, philo->input);
	philo->first_fork->fork_in_use = 0;
	philo->second_fork->fork_in_use = 0;
}

void	eat(t_philo *philo)
{
	safe_mutex(&philo->first_fork->use_mutex, 0, philo->input);
	safe_mutex(&philo->second_fork->use_mutex, 0, philo->input);
	if (philo->first_fork->fork_in_use == 0
		&& philo->second_fork->fork_in_use == 0)
		eat_routine(philo);
	safe_mutex(&philo->first_fork->use_mutex, 1, philo->input);
	safe_mutex(&philo->second_fork->use_mutex, 1, philo->input);
}
