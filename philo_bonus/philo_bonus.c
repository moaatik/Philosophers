/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:02:02 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/13 19:06:29 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void safe_print(t_philosopher *philosopher, char *msg)
{
    sem_wait(philosopher->table->print_semaphore);
    printf("%ld %d %s\n", get_time(), philosopher->id, msg);
    sem_post(philosopher->table->print_semaphore);
}

void *self_monitor(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;

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
    return NULL;
}

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
	ft_usleep(philosopher->table->eat_time);
	sem_post(*philosopher->left_fork);
	sem_post(*philosopher->right_fork);
}

void	*philosopher_day(t_philosopher *philosopher)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, &self_monitor, philosopher);
	pthread_detach(monitor_thread);
	philosopher->last_meal_date = get_time();
	if (philosopher->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (!philosopher->right_fork)
			return (safe_print(philosopher, "has taken a fork"), \
			ft_usleep(philosopher->table->time_to_die * 10), exit(0), NULL);
		eating(philosopher);
		if (philosopher->table->meals_limit != -1 && 
			philosopher->meals_eaten >= philosopher->table->meals_limit)
				exit(0);
		safe_print(philosopher, "is sleeping");
		ft_usleep(philosopher->table->sleep_time);
		safe_print(philosopher, "is thinking");
		usleep(500);
	}
	exit(0);
	return (NULL);
}

void	wait_philos(pid_t *pids, int count, t_table *table)
{
	int	i;
	int	status;
	int	finished_count;	

	finished_count = 0;
	if (table->meals_limit != -1)
	{
		while (finished_count < table->philos_number)
		{
		    waitpid(-1, &status, 0);
		    if (WEXITSTATUS(status) == 0)
		        finished_count++;
		    else
		    {
		        i = 0;
		        while (i < count)
		            kill(pids[i++], SIGKILL);
		        break;
		    }
		}
	}
	else
	{
		while (1)
		{
		    waitpid(-1, &status, 0);
		    if (WEXITSTATUS(status) != 0)
		    {
		        i = 0;
		        while (i < count)
		            kill(pids[i++], SIGKILL);
		        break;
		    }
		}
	}
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

	if (input(argc, argv, &table))
		return (1);
	if (init_semaphores(&table) || init_philosophers(&table))
		return (clean_up(&table), 1);
	dinner_time(&table);
	clean_up(&table);
}
