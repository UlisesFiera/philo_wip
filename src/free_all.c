/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all(wip).c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:08:47 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/07 09:08:47 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	detach_all(t_data *input)
{
	int	i;

	i = 0;
	while (i < input->nbr_philo)
	{
		if (input->philos[i].detached == 0)
			safe_thread(&input->philos[i].philo_thread_id, NULL, NULL, 2);
		i++;
	}
	if (input->monitor_detached == 0)
		safe_thread(&input->monitor_dead, NULL, NULL, 2);
}

void	destroy_mutex(t_data *input)
{
	int	i;
	
	i = 0;
	safe_mutex(&input->data_mutex, 3);
	safe_mutex(&input->write_mutex, 3);
	while (i < input->nbr_philo)
	{
		safe_mutex(&input->forks[i].fork_mutex, 3);
		i++;
	}
	i = 0;
	while (i < input->nbr_philo)
	{
		safe_mutex(&input->philos[i].philo_mutex, 3);
		i++;
	}
}

void	free_all(t_data *input)
{
	detach_all(input);
	destroy_mutex(input);
	if (input->forks)
		free(input->forks);
	if (input->philos)
		free(input->philos);
}
