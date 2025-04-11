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

int	eat(t_philo *philo)
{
	int	ret_value;

	ret_value = 0;
	while (get_status(&philo->philo_mutex, &philo->ready) == 0)
	{
		ret_value = get_status(&philo->philo_mutex, &philo->ready);
		if (ret_value == -1)
		{
			philo->input->end_program = 1;
			return (1);
		}
	}
	if (safe_mutex(&philo->first_fork->fork_mutex, 0))
		return (1);
	if (write_action(4, philo))
		return (1);
	if (safe_mutex(&philo->second_fork->fork_mutex, 0))
		return (1);
	if (write_action(5, philo))
		return (1);
	if (set_long(&philo->philo_mutex, &philo->time_last_meal, timestamp()))
		return (1);
	philo->meal_count++;
	if (write_action(1, philo))
		return (1);
	usleep(philo->input->time_to_eat);
	if (philo->input->nbr_max_meals > 0
		&& philo->meal_count == philo->input->nbr_max_meals)
		if (set_status(&philo->philo_mutex, &philo->full, 1))
			return (1);
	if (safe_mutex(&philo->first_fork->fork_mutex, 1))
		return (1);
	if (safe_mutex(&philo->second_fork->fork_mutex, 1))
		return (1);
	return (0);
}
