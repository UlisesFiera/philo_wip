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

static void	check_max_min(long digit, t_data *input)
{
	if (digit < -2147483648)
		error_exit("Incorrect input: All inputs should be ints", input);
	if (digit > 2147483647)
		error_exit("Incorrect input: All inputs should be ints", input);
}

static void	check_digit(const char *string, t_data *input)
{
	while (*string)
	{
		if (*string < '0' || *string > '9')
			error_exit("Incorrect input: All inputs should be ints", input);
		string++;
	}
}

static long	atol_input(const char *string, t_data *input)
{
	long	number;

	number = 0;
	while (*string == ' ' || *string == '\t' || *string == '\n'
		|| *string == '\r' || *string == '\f' || *string == 'v')
		string++;
	while (*string == '+')
		string++;
	if (*string == '-')
		error_exit("Incorrect input: All inputs should be ints", input);
	check_digit(string, input);
	while (*string)
		number = number * 10 + (*string++ - '0');
	return (number);
}

void	parse_input(t_data *input, char **argv)
{
	check_max_min(input->nbr_philo = atol_input(argv[1], input), input);
	check_max_min(input->time_to_die = (atol_input(argv[2], input) * 1e3), input);
	check_max_min(input->time_to_eat = (atol_input(argv[3], input) * 1e3), input);
	check_max_min(input->time_to_sleep  = (atol_input(argv[4], input) * 1e3), input);
	if (input->time_to_die < 6e4
		|| input->time_to_eat < 6e4
		|| input->time_to_sleep < 6e4)
		error_exit("Incorrect input: use timestamps > 60ms", input);
	if (argv[5])
		check_max_min(input->nbr_max_meals = (atol_input(argv[5], input)), input);
	else
		input->nbr_max_meals = -1;
}

/*

Notes!
-> '1en' stands for a 1 followed by n zeroes.
	-> We use it cause 'usleep' and such take microseconds and the input is a
	millisecond. The timestamp must be a ms tho!

*/