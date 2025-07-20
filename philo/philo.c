/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:02:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/20 19:19:58 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork);
	safe_print(philosopher, "has taken a fork");
	pthread_mutex_lock(philosopher->left_fork);
	safe_print(philosopher, "has taken a fork");
	philosopher->last_meal_date = get_time();
	safe_print(philosopher, "is eating");
	philosopher->meals_eaten++;
	ft_usleep(philosopher->table->eat_time, philosopher);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	*philosopher_day(void *argement)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)argement;
	while (!get_start_dinner(philosopher->table))
		usleep(10);
	philosopher->last_meal_date = get_time();
	printf("start[%ld][%d]\n", get_time() , philosopher->id);
	if (philosopher->id % 2 == 0)
		ft_usleep(1, philosopher);
	while (1)
	{
		if (get_end_dinner(philosopher->table) || !philosopher->right_fork)
			return (safe_print(philosopher, "has taken a fork"), NULL);
		eating(philosopher);
		if (philosopher->meals_eaten == philosopher->table->meals_limit)
			return (set_done_eating(philosopher->table), NULL);
		safe_print(philosopher, "is sleeping");
		ft_usleep(philosopher->table->sleep_time, philosopher);
		safe_print(philosopher, "is thinking");
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
		if (get_done_eating(table) == table->philos_number)
			return (NULL);
		while (i < table->philos_number)
		{
			if (get_time() - table->philosophers[i].last_meal_date > \
				table->time_to_die && table->philosophers[i].meals_eaten \
				!= table->meals_limit)
				return (pthread_mutex_lock(&table->print_mutex), \
					set_end_dinner(table, 1), printf("%ld %d %s\n", \
					get_time(), table->philosophers[i].id, "died"), \
					pthread_mutex_unlock(&table->print_mutex), NULL);
			i++;
		}
		ft_usleep(5, &table->philosophers[0]);
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
	set_start_dinner(table, 0);
	while (i < table->philos_number)
	{
		if (pthread_create(&threads[i], NULL, philosopher_day, \
			&table->philosophers[i]))
			return (join_threads(threads, i), 1);
		i++;
	}
	if (pthread_create(&threads[i], NULL, monitoring, table))
		return (join_threads(threads, i), 1);
	set_start_dinner(table, 1);
	join_threads(threads, i);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (input(argc, argv, &table))
		return (1);
	if (init_mutexes(&table) || init_philosophers(&table))
		return (clean_up(&table), 1);
	dinner_time(&table);
	clean_up(&table);
}
