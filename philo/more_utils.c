/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:00:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/27 18:52:09 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death(t_table *table, int i)
{
	pthread_mutex_unlock(&table->philosophers[i].meals_mutex);
	pthread_mutex_lock(&table->print_mutex);
	set_end_dinner(table, 1);
	printf("%ld %d %s\n", get_time(table), table->philosophers[i].id, "died");
	pthread_mutex_unlock(&table->print_mutex);
	return (NULL);
}

long	get_time(t_table *table)
{
	static long		start_time;
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	pthread_mutex_lock(&table->time_mutex);
	if (start_time == 0)
		start_time = current_time;
	pthread_mutex_unlock(&table->time_mutex);
	return (current_time - start_time);
}

void	set_end_dinner(t_table *table, int value)
{
	pthread_mutex_lock(&table->end_mutex);
	table->end_dinner = value;
	pthread_mutex_unlock(&table->end_mutex);
}

int	get_end_dinner(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->end_mutex);
	status = table->end_dinner;
	pthread_mutex_unlock(&table->end_mutex);
	return (status);
}

void	safe_print(t_philosopher *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->table->print_mutex);
	if (!get_end_dinner(philosopher->table))
		printf("%ld %d %s\n", get_time(philosopher->table),
			philosopher->id, msg);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}
