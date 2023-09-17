/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyap <alyap@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:41:35 by alyap             #+#    #+#             */
/*   Updated: 2023/09/17 23:44:51 by alyap            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->args->forks_array[philo->left_fork_id]));
	print_msg(philo->args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->args->forks_array[philo->right_fork_id]));
	print_msg(philo->args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->mutex_is_eating));
	philo->last_eat_timestamp = get_timestamp();
	philo->is_eating = true;
	print_msg(philo->args, philo->id, "is eating");
	usleep(philo->args->t_eating * 1000);
	pthread_mutex_unlock(&(philo->mutex_is_eating));
	philo->is_eating = false;
	pthread_mutex_unlock(&(philo->args->forks_array[philo->left_fork_id]));
	pthread_mutex_unlock(&(philo->args->forks_array[philo->right_fork_id]));
	philo->eat_count++;
}

void	check_eat(t_args *args)
{
	unsigned int	i;
	unsigned int	n_eat_times;

	i = 0;
	n_eat_times = args->n_eat_times;
	while (i < args->n_philos)
	{
		if (args->philo_array[i]->eat_count < n_eat_times)
			break ;
		i++;
	}
	if (i == args->n_philos && args->philo_array[i - 1]->eat_count
		>= n_eat_times)
	{
		pthread_mutex_lock(&(args->mutex_writing));
		args->run_simulation = false;
	}
}

void	*check_death(void *philo_v_ptr)
{
	t_philo			*philo;
	unsigned int	t_die_starving;

	philo = (t_philo *)philo_v_ptr;
	t_die_starving = philo->args->t_die_starving;
	while (philo->args->run_simulation)
	{
		if (!(philo->is_eating) && get_timestamp() - philo->last_eat_timestamp
			>= t_die_starving)
		{
			print_msg(philo->args, philo->id, "died");
			philo->args->run_simulation = false;
		}
		if (philo->args->n_eat_times != INT_MAX && philo->eat_count
			>= philo->args->n_eat_times)
			check_eat(philo->args);
		usleep(100 * 1000);
	}
	return (NULL);
}

void	*simulate_philo(void *philo_v_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_v_ptr;
	while (philo->args->run_simulation)
	{
		grab_fork_and_eat(philo);
		print_msg(philo->args, philo->id, "is sleeping");
		usleep(philo->args->t_sleeping * 1000);
		print_msg(philo->args, philo->id, "is thinking");
	}
	return (NULL);
}

void	run_simulation(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->n_philos)
	{
		args->philo_array[i]->last_eat_timestamp = get_timestamp();
		pthread_create(&args->philo_array[i]->philo_thread, NULL,
			simulate_philo, (void *)args->philo_array[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < args->n_philos)
	{
		pthread_create(&args->philo_array[i]->check_death_thread, NULL,
			check_death, (void *)args->philo_array[i]);
		i++;
		usleep(100);
	}
}
