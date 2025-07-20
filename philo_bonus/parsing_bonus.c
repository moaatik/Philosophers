/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:25:21 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/20 18:25:40 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_is_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	input(int ac, char **av, t_table *table)
{
	int	error;
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (write(2, "Error\nUsage Example: ./philo philosophers_number \
time_to_die eat_time sleep_time max_meals(optional)\n", 101), 1);
	while (av[i])
	{
		error = 0;
		if (ft_atoi(av[i], &error) <= 0 || error || ft_is_digit(av[i]))
			return (write(2, "Error\ninvalid argument\n", 23), 1);
		i++;
	}
	table->philos_number = ft_atoi(av[1], &error);
	table->time_to_die = ft_atoi(av[2], &error);
	table->eat_time = ft_atoi(av[3], &error);
	table->sleep_time = ft_atoi(av[4], &error);
	table->meals_limit = -1;
	if (ac == 6)
		table->meals_limit = ft_atoi(av[5], &error);
	table->philos_done_eating = 0;
	table->philosophers = NULL;
	return (0);
}

void	handle_max_meals(pid_t *pids, int count, t_table *table, int i)
{
	int	finished_count;
	int	status;

	finished_count = 0;
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
			return ;
		}
	}
}

void	wait_philos(pid_t *pids, int count, t_table *table)
{
	int	i;
	int	status;

	if (table->meals_limit != -1)
		handle_max_meals(pids, count, table, 0);
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
				break ;
			}
		}
	}
	free(pids);
}
