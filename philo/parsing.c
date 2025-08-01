/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:25:21 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/01 08:22:49 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == 32)
		i++;
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
		if (ft_atoi(av[i], &error) < 0 || error || ft_is_digit(av[i]))
			return (write(2, "Error\nInvalid argument\n", 23), 1);
		i++;
	}
	init_table(ac, av, table);
	return (0);
}

void	set_done_eating(t_table *table)
{
	pthread_mutex_lock(&table->done_eating_mutex);
	table->philos_done_eating++;
	pthread_mutex_unlock(&table->done_eating_mutex);
}

int	get_done_eating(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->done_eating_mutex);
	status = table->philos_done_eating;
	pthread_mutex_unlock(&table->done_eating_mutex);
	return (status);
}

void	sleeping(t_philosopher *philosopher)
{
	int	sleep_time;

	safe_print(philosopher, "is sleeping");
	sleep_time = philosopher->table->sleep_time;
	if (!sleep_time)
		sleep_time = 1;
	ft_usleep(sleep_time, philosopher);
}
