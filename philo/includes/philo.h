/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyap <alyap@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:41:10 by alyap             #+#    #+#             */
/*   Updated: 2023/09/17 23:49:55 by alyap            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>

typedef struct s_args	t_args;

typedef struct s_philo
{
	pthread_t			philo_thread;
	pthread_t			check_death_thread;
	t_args				*args;
	unsigned int		id;
	pthread_mutex_t		mutex_is_eating;
	long long unsigned	last_eat_timestamp;
	unsigned int		eat_count;
	unsigned int		left_fork_id;
	unsigned int		right_fork_id;
	bool				is_eating;
}	t_philo;

typedef struct s_args
{
	unsigned int	n_philos;
	unsigned int	t_die_starving;
	unsigned int	t_eating;
	unsigned int	t_sleeping;
	unsigned int	n_eat_times;
	pthread_mutex_t	mutex_writing;
	unsigned long	t_start;
	pthread_mutex_t	*forks_array;
	t_philo			**philo_array;
	bool			run_simulation;
}	t_args;

void				ft_free_all(t_args *args);
long long unsigned	get_timestamp(void);
void				print_msg(t_args *args, unsigned int philo_id, char *str);
int					ft_atoi(char *num_str);
bool				parse_args(int argc, char **args);
t_args				*init(int argc, char **argv);
void				run_simulation(t_args *args);

#endif
