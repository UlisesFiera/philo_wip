/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:11:12 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/08 13:11:12 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	increase_long(t_mutex *mutex, long *value)
{
	if (safe_mutex(mutex, 0))
		return (1);
	(*value)++;
	if (safe_mutex(mutex, 1))
		return (1);
	return (0);
}
