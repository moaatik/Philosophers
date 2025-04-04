/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:18:06 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/04 17:56:09 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->philos_number);
	if (!forks)
		return (1);
	while (i < table->philos_number)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	table->forks = forks;
	retrun (0);
}

int	init_philosophers(t_table *table)
{
	int				i;
	t_philosopher	*philosophers;

	i = 1;
	philosophers = malloc(sizeof(t_philosopher) * table->philos_number);
	if (!philosophers)
		return 1;
	table->philosophers = philosophers;
	while (i <= table->philos_number)
	{
		table->philosophers->id = i;
		table->philosophers->last_meal_date = 0;
		table->philosophers->meals_eaten = 0;
		table->philosophers->left_fork = &table->forks[i - 1];
		if (i == 1)
			table->philosophers->right_fork = &table->forks[table->philos_number - 1];
		else
			table->philosophers->right_fork = &table->forks[i - 2];
	}
	return (0);
}
		