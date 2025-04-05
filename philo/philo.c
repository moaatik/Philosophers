/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:02:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/05 13:34:36 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void	*philosopher_routine(void *argement)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)argement;
	while (1)
	{
		if (get_time() - philosopher->last_meal_date > philosopher->table->time_to_die)
		{
			pthread_mutex_unlock(philosopher->left_fork);
			pthread_mutex_unlock(philosopher->right_fork);
			printf("%ld : Philosopher %d died\n", get_time(), philosopher->id);
			break ;
		}
		
		if (philosopher->id % 2 == 0)
			usleep(100);
		
		pthread_mutex_lock(philosopher->left_fork);
		printf("%ld : Philosopher %d has taken his left fork\n", get_time(), philosopher->id);
		pthread_mutex_lock(philosopher->right_fork);
		printf("%ld : Philosopher %d has taken his right fork\n", get_time(), philosopher->id);

		printf("%ld : Philosopher %d is eating\n", get_time(), philosopher->id);
		philosopher->last_meal_date = get_time();
		philosopher->meals_eaten++;
		//printf("====Philosopher %d have eates %d meals=====\n", philosopher->id, philosopher->meals_eaten);
		usleep(1000 * philosopher->table->eat_time);
		
		pthread_mutex_unlock(philosopher->left_fork);
		//printf("%ld : Philosopher %d has put down his left fork\n", get_time(), philosopher->id);
		pthread_mutex_unlock(philosopher->right_fork);
		//printf("%ld : Philosopher %d has put down his right fork\n", get_time(), philosopher->id);
		
		printf("%ld : Philosopher %d is sleeping\n", get_time(), philosopher->id);
		usleep(1000 * philosopher->table->sleep_time);
		
		printf("%ld : Philosopher %d is thinking\n", get_time(), philosopher->id);
		usleep(1000 * philosopher->table->think_time);
		
	}
	return (NULL);
}

int	dinner_time(t_table *table)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * table->philos_number);
	if (!threads)
		return (1);
	while (i < table->philos_number)
	{
		if (pthread_create(&threads[i], NULL, philosopher_routine, &table->philosophers[i]))
			return (free(threads), 1);
		table->philosophers[i].last_meal_date = get_time();
		i++;
	}
	i = 0;
	while (i < table->philos_number)
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
