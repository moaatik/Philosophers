/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:25:21 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/05 08:41:41 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	table->philos_done_eating = 0;
	table->philosophers = NULL;
	table->usleep_time = get_usleep_time(table);
	table->start_time = 0;
	table->print_semaphore = NULL;
	table->forks = NULL;
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
