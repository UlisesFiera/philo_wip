/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 10:45:19 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/06 10:45:19 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, int startup)
{
	long	time_to_think;

	safe_mutex(&philo->input->data_mutex, 0, philo->input);
	time_to_think = ((philo->input->time_to_die
				- (timestamp(philo->input) - philo->time_last_meal)
				- philo->input->time_to_eat) / 2) / 1e3;
	if (time_to_think > philo->input->time_to_die / 2)
		time_to_think = time_to_think / 2;
	safe_mutex(&philo->input->data_mutex, 1, philo->input);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && startup == 1)
		time_to_think = 1;
	if (startup == 0)
		write_action(3, philo);
	precise_usleep(time_to_think);
}
