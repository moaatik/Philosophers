/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:02:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/08 13:30:46 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	get_end_dinner(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->end_mutex);
	status = table->end_dinner;
	pthread_mutex_unlock(&table->end_mutex);
	return (status);
}

void	set_end_dinner(t_table *table, int value)
{
	pthread_mutex_lock(&table->end_mutex);
	table->end_dinner = value;
	pthread_mutex_unlock(&table->end_mutex);
}

void	safe_print(t_philosopher *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->table->print_mutex);
	if (!get_end_dinner(philosopher->table))
		printf("%ld %d %s\n", get_time(), philosopher->id, msg);
	pthread_mutex_unlock(&philosopher->table->print_mutex);
}

void	*philosopher_day(void *argement)
{
	t_philosopher	*philosopher;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philosopher = (t_philosopher *)argement;
	first = philosopher->left_fork;
	second = philosopher->right_fork;
	while (1)
	{
		if (get_end_dinner(philosopher->table))
			return (NULL);

		if (philosopher->id % 2 == 0)
			usleep(100);

		if (first > second)
		{
			first = philosopher->right_fork;
			second = philosopher->left_fork;
		}

		// pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(first);
		safe_print(philosopher, "has taken a fork");
		if (!philosopher->right_fork)
			return (NULL);
		// pthread_mutex_lock(philosopher->right_fork);
		pthread_mutex_lock(second);
		safe_print(philosopher, "has taken a fork");

		safe_print(philosopher, "is eating");
		philosopher->last_meal_date = get_time();
		philosopher->meals_eaten++;
		usleep(1000 * philosopher->table->eat_time);
		
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		
		if (philosopher->meals_eaten == philosopher->table->meals_limit)
			return (NULL);

		safe_print(philosopher, "is sleeping");
		usleep(1000 * philosopher->table->sleep_time);

		
		philosopher->think_time = (philosopher->table->time_to_die - (get_time() - philosopher->last_meal_date)) / 2;
		if (philosopher->think_time < 0)
			philosopher->think_time = 0;
		if (philosopher->think_time > 600)
			philosopher->think_time = 200;

		
		safe_print(philosopher, "is thinking");
		usleep(1000 * philosopher->think_time);
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
		while (i < table->philos_number)
		{
			if (get_time() - table->philosophers[i].last_meal_date >= table->time_to_die)
			{
				pthread_mutex_lock(&table->print_mutex);
				if (!get_end_dinner(table))
				{
					set_end_dinner(table, 1);
					printf("%ld %d died\n", get_time(), table->philosophers[i].id);
				}
				pthread_mutex_unlock(&table->print_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
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
		if (pthread_create(&threads[i], NULL, philosopher_day, &table->philosophers[i]))
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

	if (input(argc, argv, &table) || init_forks(&table) || init_philosophers(&table)|| dinner_time(&table))
		return (1);
}
