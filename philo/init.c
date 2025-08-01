/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:18:06 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/01 08:19:16 by moaatik          ###   ########.fr       */
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

int	give_forks(t_table *table, int i)
{
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
	if (pthread_mutex_init(&table->philosophers[i].is_eating_mutex, NULL))
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
		table->philosophers[i].is_eating = 0;
		if (give_forks(table, i))
			return (1);
		table->philosophers[i++].table = table;
	}
	return (0);
}

int	get_usleep_time(t_table *table)
{
	float	a;
	float	b;
	float	result;

	a = 3.7878787878788;
	b = 42.424242424242;
	result = (table->philos_number * a) + b;
	return ((int)result);
}

void	init_table(int ac, char **av, t_table *table)
{
	int	error;

	table->philos_number = ft_atoi(av[1], &error);
	table->time_to_die = ft_atoi(av[2], &error);
	table->eat_time = ft_atoi(av[3], &error);
	table->sleep_time = ft_atoi(av[4], &error);
	table->meals_limit = -1;
	if (ac == 6)
		table->meals_limit = ft_atoi(av[5], &error);
	table->end_dinner = 0;
	table->philos_done_eating = 0;
	table->philosophers = NULL;
	table->usleep_time = get_usleep_time(table);
}
