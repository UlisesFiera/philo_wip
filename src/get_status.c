/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:10:01 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 12:10:01 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_status(t_mutex *mutex, int *status)
{
	int	ret_value;

	safe_mutex(mutex, 0);
	ret_value = *status;
	safe_mutex(mutex, 1);
	return (ret_value);
}
