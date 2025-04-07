/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:12:12 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/03 14:12:12 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	if (data->philos)
	{
		if (data->philos->first_fork)
			free(data->philos->first_fork);
		if (data->philos->second_fork)
			free(data->philos->second_fork);
		if (data->philos->input)
			free_all(data->philos->input);
		free(data->philos);
	}
	if (data->forks)
		free(data->forks);
}

void	error_exit(char *error, t_data *data)
{
	free_all(data);
	printf(R "%s" RST "\n", error);
	exit(EXIT_FAILURE);
}
