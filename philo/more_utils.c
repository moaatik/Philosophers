/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:00:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/11 16:47:12 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_start_dinner(t_table *table, int value)
{
	pthread_mutex_lock(&table->start_mutex);
	table->start_dinner = value;
	pthread_mutex_unlock(&table->start_mutex);
}

int	get_start_dinner(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->start_mutex);
	status = table->start_dinner;
	pthread_mutex_unlock(&table->start_mutex);
	return (status);
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
		printf("%ld %d %s\n", get_time(), philosopher->id, msg);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}
