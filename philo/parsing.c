/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:25:21 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/11 16:23:43 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (ft_atoi(av[i++], &error) <= 0 || error)
			return (write(2, "Error\ninvalid argument\n", 43), 1);
	}
	table->philos_number = ft_atoi(av[1], &error);
	table->time_to_die = ft_atoi(av[2], &error);
	table->eat_time = ft_atoi(av[3], &error);
	table->sleep_time = ft_atoi(av[4], &error);
	table->meals_limit = -1;
	if (ac == 6)
		table->meals_limit = ft_atoi(av[5], &error);
	table->end_dinner = 0;
	table->philos_done_eating = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->end_mutex, NULL);
	return (0);
}
