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

void	increase_long(t_mutex *mutex, long *value, t_data *input)
{
	safe_mutex(mutex, 0, input);
	(*value)++;
	safe_mutex(mutex, 1, input);
}
