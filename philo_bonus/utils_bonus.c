/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/22 19:15:54 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (str[i])
		if (str[i++] != 32)
			return (*error = 1, result * sign);
	return (result * sign);
}

long	get_time(void)
{
	static long		start_time;
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (start_time == 0)
		start_time = current_time;
	return (current_time - start_time);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

void	clean_up(t_table *table)
{
	if (table->forks)
		sem_close(table->forks);
	sem_unlink("/print");
	if (table->print_semaphore)
		sem_close(table->print_semaphore);
	sem_unlink("/print");
	if (table->philosophers)
		free(table->philosophers);
}

void	safe_print(t_philosopher *philosopher, char *msg)
{
	char	*temp;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	sem_wait(philosopher->table->print_semaphore);
	temp2 = ft_itoa(get_time());
	temp3 = ft_itoa(philosopher->id);
	temp = ft_strjoin_3(temp2, " ", temp3);
	free(temp2);
	free(temp3);
	temp1 = ft_strjoin_3(temp, msg, NULL);
	free(temp);
	write(1, temp1, ft_strlen(temp1));
	free(temp1);
	sem_post(philosopher->table->print_semaphore);
}
