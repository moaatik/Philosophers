/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:02:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/11 18:58:22 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		sem_wait(*philosopher->right_fork);
		safe_print(philosopher, "has taken a fork");
		sem_wait(*philosopher->left_fork);
		safe_print(philosopher, "has taken a fork");
	}
	else
	{
		sem_wait(*philosopher->left_fork);
		safe_print(philosopher, "has taken a fork");
		sem_wait(*philosopher->right_fork);
		safe_print(philosopher, "has taken a fork");
	}
	philosopher->last_meal_date = get_time();
	safe_print(philosopher, "is eating");
	philosopher->meals_eaten++;
	ft_usleep(philosopher->table->eat_time, philosopher);
	sem_post(*philosopher->left_fork);
	sem_post(*philosopher->right_fork);
}

void	*philosopher_day(t_philosopher *philosopher)
{
	philosopher->last_meal_date = get_time();
	if (philosopher->id % 2 == 0)
		ft_usleep(1, philosopher);
	while (1)
	{
		if (get_end_dinner(philosopher->table) || !philosopher->right_fork)
			return (exit(0), NULL);
		eating(philosopher);
		if (philosopher->meals_eaten == philosopher->table->meals_limit)
			return (philosopher->table->philos_done_eating++, exit(0), NULL);
		safe_print(philosopher, "is sleeping");
		ft_usleep(philosopher->table->sleep_time, philosopher);
		safe_print(philosopher, "is thinking");
		usleep(500);
	}
	exit(0);
	return (NULL);
}

void	*monitoring(t_table *table)
{
	int		i;

	while (1)
	{
		i = 0;
		if (table->philos_done_eating == table->philos_number)
			return (exit(0), NULL);
		while (i < table->philos_number)
		{
			if (get_time() - table->philosophers[i].last_meal_date >= \
				table->time_to_die && table->philosophers[i].meals_eaten \
				!= table->meals_limit)
				return (set_end_dinner(table, 1), printf("%ld %d %s\n", \
				get_time(), table->philosophers[i].id, "died"), NULL);
			i++;
		}
	}
	exit(0);
	return (NULL);
}

void	wait_philos(pid_t *pids, int count)
{
	int		i;

	waitpid(-1, NULL, 0);
	for (i = 0; i < count; i++)
		kill(pids[i], SIGKILL);
	free(pids);
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
		table->philosophers[index].id = index;
		pids[index] = fork();
		if (pids[index] < 0)
			return (free(pids), 1);
		if (pids[index] == 0)
			philosopher_day(&table->philosophers[index]);
		index++;
	}
	pids[index] = fork();
	if (pids[index] < 0)
		return (free(pids), 1);
	if (pids[index] == 0)
		monitoring(table);
	wait_philos(pids, index);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (input(argc, argv, &table))
		return (1);
	if (init_semaphores(&table) || init_philosophers(&table))
		return (clean_up(&table), 1);
	dinner_time(&table);
	clean_up(&table);
}
