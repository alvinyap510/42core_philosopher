/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyap <alyap@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:41:14 by alyap             #+#    #+#             */
/*   Updated: 2023/11/21 10:39:39 by alyap            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_fork_id(t_args *args, t_philo *philo)
{
	unsigned int	n_philos;

	n_philos = args->n_philos;
	if (philo->id == n_philos - 1)
	{
		philo->left_fork_id = philo->id;
		philo->right_fork_id = 0;
	}
	else
	{
		philo->left_fork_id = philo->id;
		philo->right_fork_id = philo->id + 1;
	}
}

pthread_mutex_t	*init_forks(unsigned int n_philos)
{
	pthread_mutex_t	*forks_array;
	unsigned int	i;

	i = 0;
	forks_array = malloc(sizeof(pthread_mutex_t) * n_philos);
	if (!forks_array)
		return (NULL);
	while (i < n_philos)
	{
		pthread_mutex_init(&forks_array[i], NULL);
		i++;
	}
	return (forks_array);
}

t_philo	**init_philo(t_args *args)
{
	t_philo			**philo_array;
	unsigned int	i;

	philo_array = (t_philo **)malloc(sizeof(t_philo *) * args->n_philos);
	if (!philo_array)
		return (NULL);
	i = 0;
	while (i < args->n_philos)
	{
		philo_array[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (!philo_array[i])
			return (NULL);
		philo_array[i]->args = args;
		philo_array[i]->id = i;
		pthread_mutex_init(&philo_array[i]->mutex_is_eating, NULL);
		philo_array[i]->eat_count = 0;
		assign_fork_id(args, philo_array[i]);
		i++;
	}
	return (philo_array);
}

t_args	*init(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args) * 1);
	if (!args)
		return (NULL);
	args->n_philos = ft_atoi(argv[1]);
	args->t_die_starving = ft_atoi(argv[2]);
	args->t_eating = ft_atoi(argv[3]);
	args->t_sleeping = ft_atoi(argv[4]);
	if (argc == 6)
		args->n_eat_times = ft_atoi(argv[5]);
	else
		args->n_eat_times = INT_MAX;
	pthread_mutex_init(&(args->mutex_writing), NULL);
	args->forks_array = init_forks(args->n_philos);
	args->philo_array = init_philo(args);
	if (!args->forks_array || !args->philo_array)
		return (NULL);
	return (args);
}
