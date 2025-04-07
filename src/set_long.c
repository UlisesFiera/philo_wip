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

void	set_long(t_mutex *mutex, long *number, long value, t_data *input)
{
	safe_mutex(mutex, 0, input);
	*number = value;
	safe_mutex(mutex, 1, input);
}
