/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:07:43 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 12:07:43 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_status(t_mutex *mutex, int *status, int value, t_data *input)
{
	safe_mutex(mutex, 0, input);
	*status = value;
	safe_mutex(mutex, 1, input);
}
