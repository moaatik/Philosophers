/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:00:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/12 17:37:02 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_end_dinner(t_table *table, int value)
{
	sem_wait(table->end_semaphore);
	table->end_dinner = value;
	sem_post(table->end_semaphore);
}

int	get_end_dinner(t_table *table)
{
	int	status;

	sem_wait(table->end_semaphore);
	status = table->end_dinner;
	sem_post(table->end_semaphore);
	return (status);
}

void	safe_print(t_philosopher *philosopher, char *msg)
{
	sem_wait(philosopher->table->print_semaphore);
	if (!get_end_dinner(philosopher->table))
		printf("%ld %d %s\n", get_time(), philosopher->id, msg);
	sem_post(philosopher->table->print_semaphore);
}
