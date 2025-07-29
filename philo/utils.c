/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/29 22:34:18 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	check_spaces(const char *str, int *error, long result, int i)
{
	while (str[i])
		if (str[i++] != 32)
			return (*error = 1, result);
	return (result);
}

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
	return (check_spaces(str, error, result * sign, i));
}

void	ft_usleep(long ms, t_philosopher *philosopher)
{
	long	start;

	start = get_time(philosopher->table);
	while (!get_end_dinner(philosopher->table)
		&& (get_time(philosopher->table) - start) < ms)
		usleep(philosopher->table->usleep_time);
}

void	join_threads(pthread_t	*threads, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		pthread_join(threads[j], NULL);
		j++;
	}
	free(threads);
}

void	clean_up(t_table *table)
{
	int	i;

	i = 0;
	while (table->forks && i < table->philos_number)
		pthread_mutex_destroy(&table->forks[i++]);
	i = 0;
	while (table->philosophers && i < table->philos_number)
	{
		pthread_mutex_destroy(&table->philosophers[i].meals_mutex);
		pthread_mutex_destroy(&table->philosophers[i++].is_eating_mutex);
	}
	pthread_mutex_destroy(&table->end_mutex);
	pthread_mutex_destroy(&table->time_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->done_eating_mutex);
	free(table->forks);
	free(table->philosophers);
}
