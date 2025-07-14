/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:18:06 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/14 14:21:09 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_table *table, char *name, char *name1, int i)
{
	sem_t	**forks;

	forks = malloc(sizeof(sem_t *) * table->philos_number);
	if (!forks)
		return (1);
	while (i < table->philos_number)
	{
		name1 = ft_itoa(i);
		name = ft_strjoin("/fork", name1);
		free(name1);
		sem_unlink(name);
		forks[i] = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
		free(name);
		if (forks[i++] == SEM_FAILED)
			return (1);
	}
	table->forks = forks;
	sem_unlink("/print");
	sem_unlink("/death_sem");
	table->death_semaphore = sem_open("/death_sem", O_CREAT | O_EXCL, 0644, 0);
	table->print_semaphore = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (table->print_semaphore == SEM_FAILED \
		|| table->death_semaphore == SEM_FAILED)
		return (1);
	return (0);
}

int	init_philosophers(t_table *table)
{
	int				i;
	t_philosopher	*philosophers;

	i = 0;
	philosophers = malloc(sizeof(t_philosopher) * table->philos_number);
	if (!philosophers)
		return (1);
	table->philosophers = philosophers;
	while (i < table->philos_number)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_date = 0;
		philosophers[i].meals_eaten = 0;
		philosophers[i].think_time = 0;
		philosophers[i].left_fork = &table->forks[i];
		if (table->philos_number < 2)
			philosophers[i].right_fork = NULL;
		else if (i == 0)
			philosophers[i].right_fork = \
			&table->forks[table->philos_number - 1];
		else
			philosophers[i].right_fork = &table->forks[i - 1];
		philosophers[i++].table = table;
	}
	return (0);
}
