/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:00:54 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/11 16:47:12 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str, int *error)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	*error = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result * sign > 2147483647 || result * sign < -2147483648)
			return (*error = 1, result * sign);
		i++;
	}
	return (result * sign);
}

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_number)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->end_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philosophers);
}
