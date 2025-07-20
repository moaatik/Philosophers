/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:14:49 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/20 22:03:13 by moaatik          ###   ########.fr       */
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
