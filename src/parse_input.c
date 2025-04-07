/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:39:31 by ulfernan          #+#    #+#             */
/*   Updated: 2025/04/04 10:39:31 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_max_min(long digit)
{
	if (digit < -1)
		return (1);
	if (digit > 2147483647)
	{
		error_exit("Incorrect input: All inputs should be ints");
		return (1);
	}
	return (0);
}

static void	check_digit(const char *string)
{
	while (*string)
	{
		if (*string < '0' || *string > '9')
			error_exit("Incorrect input: All inputs should be ints");
		string++;
	}
}

static long	atol_input(const char *string)
{
	long	number;

	number = 0;
	while (*string == ' ' || *string == '\t' || *string == '\n'
		|| *string == '\r' || *string == '\f' || *string == 'v')
		string++;
	while (*string == '+')
		string++;
	if (*string == '-')
	{
		error_exit("Incorrect input: All ints should be positive");
		return (-1);
	}
	check_digit(string);
	while (*string)
		number = number * 10 + (*string++ - '0');
	return (number);
}

int	parse_input(t_data *input, char **argv)
{
	if (check_max_min(input->nbr_philo = (atol_input(argv[1]))))
		return (1);
	if (check_max_min(input->time_to_die = (atol_input(argv[2]) * 1e3)))
		return (1);
	if (check_max_min(input->time_to_eat = (atol_input(argv[3]) * 1e3)))
		return (1);
	if (check_max_min(input->time_to_sleep  = (atol_input(argv[4]) * 1e3)))
		return (1);
	if (input->time_to_die < 6e4
		|| input->time_to_eat < 6e4
		|| input->time_to_sleep < 6e4)
	{
		error_exit("Incorrect input: use timestamps > 60ms");
		return (1);
	}
	if (argv[5])
	{
		if (check_max_min(input->nbr_max_meals = (atol_input(argv[5]))))
			return (1);
	}
	else
		input->nbr_max_meals = -1;
	return (0);
}

/*

Notes!
-> '1en' stands for a 1 followed by n zeroes.
	-> We use it cause 'usleep' and such take microseconds and the input is a
	millisecond. The timestamp must be a ms tho!

*/