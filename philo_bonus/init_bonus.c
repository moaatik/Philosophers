/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:18:06 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/13 17:15:22 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	count(long i)
{
	int	count;

	if (i == 0)
		return (1);
	count = 0;
	while (i > 0)
	{
		i /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;

	len = count(n);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = 0;
	len--;
	while (len >= 0)
	{
		ptr[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1[i])
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ptr[j++] = s2[i++];
	ptr[j] = 0;
	return (ptr);
}

int	init_semaphores(t_table *table)
{
	sem_t	**forks;
	char	*name;
	char	*name1;
	int		i;

	forks = malloc(sizeof(sem_t *) * table->philos_number);
	if (!forks)
		return (1);
	i = 0;
	while (i < table->philos_number)
	{
		name1 = ft_itoa(i);
		name = ft_strjoin("/fork", name1);
		free(name1);
		sem_unlink(name);
		forks[i] = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
		free(name);
		if (forks[i] == SEM_FAILED)
			return (1);
		i++;
	}
	table->forks = forks;

	sem_unlink("/print");
	sem_unlink("/death_sem");

    table->death_semaphore = sem_open("/death_sem", O_CREAT | O_EXCL, 0644, 0);
    if (table->death_semaphore == SEM_FAILED)
        return (1);

	table->print_semaphore = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);

	if (table->print_semaphore == SEM_FAILED)
		return (1);
	return (0);
}

int	init_philosophers(t_table *table)
{
	int				i;
	t_philosopher	*philosophers;

	i = 0;
	philosophers = malloc(sizeof(t_philosopher) * table->philos_number);
	if (!philosophers)
		return (1);
	table->philosophers = philosophers;
	while (i < table->philos_number)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_date = 0;
		philosophers[i].meals_eaten = 0;
		philosophers[i].think_time = 0;
		philosophers[i].left_fork = &table->forks[i];
		if (table->philos_number < 2)
			philosophers[i].right_fork = NULL;
		else if (i == 0)
			philosophers[i].right_fork = \
			&table->forks[table->philos_number - 1];
		else
			philosophers[i].right_fork = &table->forks[i - 1];
		philosophers[i++].table = table;
	}
	return (0);
}
