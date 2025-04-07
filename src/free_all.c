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

void	free_all(t_data *data)
{
	int	i;

	safe_mutex(&data->data_mutex, 3);
	safe_mutex(&data->write_mutex, 3);
	i = 0;
	if (data->forks)
	{
		while (i < data->nbr_philo)
		{
			safe_mutex(&data->forks[i].fork_mutex, 3);
			i++;
		}
		free(data->forks);
	}
	i = 0;
	if (data->philos)
	{
		while (i < data->nbr_philo)
		{
			safe_mutex(&data->philos[i].philo_mutex, 3);
			i++;
		}
		free(data->philos);
	}
}
		
