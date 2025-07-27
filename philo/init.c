/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:18:06 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/27 18:09:38 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->philos_number);
	if (!forks)
		return (1);
	while (i < table->philos_number)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		i++;
	}
	table->forks = forks;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0
		|| pthread_mutex_init(&table->end_mutex, NULL) != 0
		|| pthread_mutex_init(&table->time_mutex, NULL) != 0
		|| pthread_mutex_init(&table->done_eating_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_philosophers(t_table *table)
{
	int				i;

	i = 0;
	table->philosophers = malloc(sizeof(t_philosopher) * table->philos_number);
	if (!table->philosophers)
		return (1);
	while (i < table->philos_number)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal_date = 0;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].think_time = 0;
		table->philosophers[i].left_fork = &table->forks[i];
		if (table->philos_number < 2)
			table->philosophers[i].right_fork = NULL;
		else if (i == 0)
			table->philosophers[i].right_fork = \
			&table->forks[table->philos_number - 1];
		else
			table->philosophers[i].right_fork = &table->forks[i - 1];
		if (pthread_mutex_init(&table->philosophers[i].meals_mutex, NULL) != 0)
			return (1);
		table->philosophers[i++].table = table;
	}
	return (0);
}
