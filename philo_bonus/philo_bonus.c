/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:02:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/22 22:12:36 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*self_monitor(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (get_time() - philo->last_meal_date > philo->table->time_to_die)
		{
			sem_wait(philo->table->print_semaphore);
			printf("%ld %d died\n", get_time(), philo->id);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}

void	eating(t_philosopher *philosopher)
{
	sem_wait(philosopher->table->forks);
	safe_print(philosopher, " has taken a fork\n");
	sem_wait(philosopher->table->forks);
	safe_print(philosopher, " has taken a fork\n");
	philosopher->last_meal_date = get_time();
	safe_print(philosopher, " is eating\n");
	philosopher->meals_eaten++;
	ft_usleep(philosopher->table->eat_time);
	sem_post(philosopher->table->forks);
	sem_post(philosopher->table->forks);
}

void	*philosopher_day(t_philosopher *philosopher)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, &self_monitor, philosopher);
	pthread_detach(monitor_thread);
	philosopher->last_meal_date = get_time();
	if (philosopher->id % 2 == 0)
		ft_usleep(5);
	while (1)
	{
		eating(philosopher);
		if (philosopher->table->meals_limit != -1
			&& philosopher->meals_eaten >= philosopher->table->meals_limit)
			exit(0);
		safe_print(philosopher, " is sleeping\n");
		ft_usleep(philosopher->table->sleep_time);
		safe_print(philosopher, " is thinking\n");
	}
	exit(0);
	return (NULL);
}

int	dinner_time(t_table *table)
{
	int			index;
	pid_t		*pids;

	index = 0;
	pids = malloc(sizeof(pid_t) * table->philos_number + 1);
	if (!pids)
		return (1);
	while (index < table->philos_number)
	{
		table->philosophers[index].id = index + 1;
		pids[index] = fork();
		if (pids[index] < 0)
			return (free(pids), 1);
		if (pids[index] == 0)
			philosopher_day(&table->philosophers[index]);
		index++;
	}
	wait_philos(pids, index, table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (input(argc, argv, &table) || init_semaphores(&table))
		return (1);
	if (init_philosophers(&table))
		return (clean_up(&table), 1);
	dinner_time(&table);
	clean_up(&table);
}
