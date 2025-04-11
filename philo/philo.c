/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:02:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/11 15:57:56 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	safe_print(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->right_fork);
	safe_print(philosopher, "has taken a fork");
	philosopher->last_meal_date = get_time();
	safe_print(philosopher, "is eating");
	philosopher->meals_eaten++;
	ft_usleep(philosopher->table->eat_time);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	*philosopher_day(void *argement)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)argement;
	while (1)
	{
		if (get_end_dinner(philosopher->table) || !philosopher->right_fork)
			return (NULL);
		if (philosopher->id % 2 == 0)
			ft_usleep(1);
		eating(philosopher);
		if (philosopher->meals_eaten == philosopher->table->meals_limit)
			return (philosopher->table->philos_done_eating++, NULL);
		safe_print(philosopher, "is sleeping");
		ft_usleep(philosopher->table->sleep_time);
		safe_print(philosopher, "is thinking");
		ft_usleep(1);
	}
	return (NULL);
}

void	*monitoring(void *argement)
{
	t_table	*table;
	int		i;

	table = (t_table *)argement;
	while (1)
	{
		i = 0;
		if (table->philos_done_eating == table->philos_number)
			return (NULL);
		while (i < table->philos_number)
		{
			if (get_time() - table->philosophers[i].last_meal_date >= \
				table->time_to_die && table->philosophers[i].meals_eaten \
				!= table->meals_limit)
				return (safe_print(&table->philosophers[i], "died"), \
					set_end_dinner(table, 1), NULL);
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

int	dinner_time(t_table *table)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * (table->philos_number + 1));
	if (!threads)
		return (1);
	while (i < table->philos_number)
	{
		table->philosophers[i].last_meal_date = get_time();
		if (pthread_create(&threads[i], NULL, philosopher_day, \
			&table->philosophers[i]))
			return (free(threads), 1);
		i++;
	}
	if (pthread_create(&threads[i], NULL, monitoring, table))
		return (free(threads), 1);
	i = 0;
	while (i <= table->philos_number)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (input(argc, argv, &table) || init_forks(&table) \
	|| init_philosophers(&table) || dinner_time(&table))
		return (1);
}
