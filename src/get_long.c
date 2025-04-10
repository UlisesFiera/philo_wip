/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:13:48 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 12:13:48 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_long(t_mutex *mutex, long *number)
{
	long	ret_value;

	if (safe_mutex(mutex, 0))
		return (-1);
	ret_value = *number;
	if (safe_mutex(mutex, 1))
		return (-1);
	return (ret_value);
}
