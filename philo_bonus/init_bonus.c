/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:18:06 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/01 08:25:22 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_table *table)
{
	sem_unlink("/forks");
	table->forks = sem_open("/forks", O_CREAT, 0644, table->philos_number);
	sem_unlink("/print");
	table->print_semaphore = sem_open("/print", O_CREAT, 0644, 1);
	if (table->print_semaphore == SEM_FAILED || table->forks == SEM_FAILED)
		return (clean_up(table), 1);
	return (0);
}

int	open_meal_semaphore(t_philosopher *philosopher)
{
	char	*temp;
	char	*name;

	temp = ft_itoa(philosopher->id);
	if (!temp)
		return (1);
	name = ft_strjoin_3("/meal_", temp, NULL);
	if (!name)
		return (free(temp), 1);
	sem_unlink(name);
	philosopher->meal_semaphore = sem_open(name, O_CREAT, 0644, 1);
	free(temp);
	free(name);
	if (philosopher->meal_semaphore == SEM_FAILED)
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
		philosophers[i].is_eating = 0;
		philosophers[i].table = table;
		if (open_meal_semaphore(&philosophers[i]))
			return (1);
		i++;
	}
	return (0);
}
