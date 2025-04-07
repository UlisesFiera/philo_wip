/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:40:28 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/05 12:40:28 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads_ready(t_data *input)
{
	while (!get_status(&input->data_mutex, &input->all_threads_ready, input))
		;
}
