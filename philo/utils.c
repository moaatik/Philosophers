/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/11 16:01:21 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	static long		start_time;
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (start_time == 0)
		start_time = current_time;
	return (current_time - start_time);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

int	get_end_dinner(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->end_mutex);
	status = table->end_dinner;
	pthread_mutex_unlock(&table->end_mutex);
	return (status);
}

void	set_end_dinner(t_table *table, int value)
{
	pthread_mutex_lock(&table->end_mutex);
	table->end_dinner = value;
	pthread_mutex_unlock(&table->end_mutex);
}

void	safe_print(t_philosopher *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->table->print_mutex);
	if (!get_end_dinner(philosopher->table))
		printf("%ld %d %s\n", get_time(), philosopher->id, msg);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}
