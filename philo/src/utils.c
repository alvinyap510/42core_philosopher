/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alyap <alyap@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:41:28 by alyap             #+#    #+#             */
/*   Updated: 2023/09/17 23:20:45 by alyap            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->n_philos)
	{
		pthread_mutex_destroy(&(args->philo_array[i]->mutex_is_eating));
		pthread_mutex_destroy(&(args->forks_array[i]));
		i++;
	}
	pthread_mutex_destroy(&(args->mutex_writing));
	free(args->philo_array);
	free(args->forks_array);
}

bool	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*(unsigned char *)s1 - *(unsigned char *)s2 == 0)
		return (true);
	return (false);
}

long long unsigned	get_timestamp(void)
{
	struct timespec	timestamp;

	clock_gettime(CLOCK_REALTIME, &timestamp);
	return (((long long unsigned)timestamp.tv_sec * 1000)
		+ (timestamp.tv_nsec / 1000000));
}

long long unsigned	get_rounded_time(t_args *args)
{
	long long unsigned	time_elapsed;
	long long unsigned	remainder;

	time_elapsed = get_timestamp() - args->t_start;
	remainder = time_elapsed % 100;
	return (time_elapsed - remainder);
}

void	print_msg(t_args *args, unsigned int philo_id, char *str)
{
	pthread_mutex_lock(&args->mutex_writing);
	printf("%llu %u %s\n", get_rounded_time(args), philo_id + 1, str);
	if (!ft_strcmp(str, "died"))
		pthread_mutex_unlock(&args->mutex_writing);
}
