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

int	set_status(t_mutex *mutex, int *status, int value)
{
	if (safe_mutex(mutex, 0))
		return (1);
	*status = value;
	if (safe_mutex(mutex, 1))
		return (1);
	return (0);
}
