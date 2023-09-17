/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyap <alyap@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:41:32 by alyap             #+#    #+#             */
/*   Updated: 2023/09/17 23:29:42 by alyap            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

int	ft_atoi(char *num_str)
{
	int		number;
	bool	is_negative;

	number = 0;
	is_negative = false;
	while (*num_str == ' ' || *num_str == '\t' || *num_str == '\n'
		|| *num_str == '\v' || *num_str == '\f' || *num_str == '\r')
		num_str++;
	if (*num_str == '-' || *num_str == '+')
	{
		if (*num_str == '-')
			is_negative = true;
		num_str++;
	}
	while (*num_str >= '0' && *num_str <= '9')
	{
		number = (number * 10) + (*num_str - '0');
		num_str++;
	}
	if (is_negative)
		number = -number;
	return (number);
}

long long	ft_atoi_ll(char *num_str)
{
	long long	number;
	bool		is_negative;

	number = 0;
	is_negative = false;
	while (*num_str == ' ' || *num_str == '\t' || *num_str == '\n'
		|| *num_str == '\v' || *num_str == '\f' || *num_str == '\r')
		num_str++;
	if (*num_str == '-' || *num_str == '+')
	{
		if (*num_str == '-')
			is_negative = true;
		num_str++;
	}
	while (*num_str >= '0' && *num_str <= '9')
	{
		number = (number * 10) + (*num_str - '0');
		num_str++;
	}
	if (is_negative)
		number = -number;
	return (number);
}

bool	is_valid_number(char *arg)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	num = ft_atoi_ll(arg);
	if (num <= 0 || num > INT_MAX)
		return (false);
	return (true);
}

bool	parse_args(int argc, char **args)
{
	int	check;

	check = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Invalid argument counts.\n");
		return (false);
	}
	while (check < argc)
	{
		if (!is_valid_number(args[check]))
		{
			printf("Invalid argument value.\n");
			return (false);
		}
		check++;
	}
	return (true);
}
