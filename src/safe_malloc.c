/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe__malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:48:27 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/04 11:48:27 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes, t_data *input)
{
	void	*memory;

	memory = malloc(bytes);
	if (memory == NULL)
		error_exit("Malloc couldn't allocate memory", input);
	return (memory);
}