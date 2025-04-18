/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:08:20 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/03 11:08:20 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(t_data *input)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		error_exit("'gettimeofday' failure");
		set_status(&input->end_mutex, &input->end_program, 1, input);
		return (1);
	}
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
