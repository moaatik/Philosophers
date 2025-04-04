/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:25:21 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/04 17:47:24 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input(int ac, char **av, t_table *table)
{
	int	error;
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (write(2, "Error\nUsage Example: ./philo philosophers_number time_to_die eat_time sleep_time max_meals(optional)\n", 1), 101);
	while (av[i])
	{
		error = 0;
		if (ft_atoi(av[i], &error) <= 0 || error)
			return (1);
		i++;
	}
	table->philos_number = ft_atoi(av[1], &error);
	table->philosophers->time_to_die = ft_atoi(av[2], &error);
	table->philosophers->eat_time = ft_atoi(av[3], &error);
	table->philosophers->sleep_time = ft_atoi(av[4], &error);
	table->philosophers->meals_limit = -1;
	if (ac == 6)
		table->philosophers->meals_limit = ft_atoi(av[5], &error);
	return (0);
}
