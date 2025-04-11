/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:13:37 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 12:13:37 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_long(t_mutex *mutex, long *number, long value)
{
	if (safe_mutex(mutex, 0))
		return (1);
	*number = value;
	if (safe_mutex(mutex, 1))
		return (1);
	return (0);
}
