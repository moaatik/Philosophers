/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_philos_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:14:49 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/01 08:35:52 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
