/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:54:56 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/01 08:36:03 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_usleep(long ms, t_table *table)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(table->usleep_time);
}

int	clean_meal_semaphore(t_table *table, int i)
{
	char	*temp;
	char	*name;

	temp = ft_itoa(table->philosophers[i].id);
	if (!temp)
		return (1);
	name = ft_strjoin_3("/meal_", temp, NULL);
	if (!name)
		return (free(temp), 1);
	sem_close(table->philosophers[i].meal_semaphore);
	sem_unlink(name);
	free(temp);
	free(name);
	return (0);
}

void	clean_up(t_table *table)
{
	int		i;

	i = 0;
	if (table->forks)
		sem_close(table->forks);
	sem_unlink("/forks");
	if (table->print_semaphore)
		sem_close(table->print_semaphore);
	sem_unlink("/print");
	while (table->philosophers && i < table->philos_number)
		if (clean_meal_semaphore(table, i++))
			break ;
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
	if (!temp2)
		return ((void)sem_post(philosopher->table->print_semaphore));
	temp3 = ft_itoa(philosopher->id);
	if (!temp3)
		return (sem_post(philosopher->table->print_semaphore), free(temp2));
	temp = ft_strjoin_3(temp2, " ", temp3);
	free(temp2);
	free(temp3);
	if (!temp)
		return ((void)sem_post(philosopher->table->print_semaphore));
	temp1 = ft_strjoin_3(temp, msg, NULL);
	free(temp);
	if (!temp1)
		return ((void)sem_post(philosopher->table->print_semaphore));
	write(1, temp1, ft_strlen(temp1));
	free(temp1);
	sem_post(philosopher->table->print_semaphore);
}
