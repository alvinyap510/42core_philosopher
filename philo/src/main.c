/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyap <alyap@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:41:38 by alyap             #+#    #+#             */
/*   Updated: 2023/09/17 23:22:02 by alyap            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	*args;

	if (!parse_args(argc, argv))
		return (1);
	args = init(argc, argv);
	if (!args)
		return (1);
	args->run_simulation = true;
	args->t_start = get_timestamp();
	run_simulation(args);
	while (args->run_simulation)
		continue ;
	if (!args->run_simulation)
		ft_free_all(args);
	return (0);
}
