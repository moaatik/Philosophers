/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/03 11:17:41 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;


typedef struct	s_philosopher
{
	int			id;
	pthread_t	thread_id;
	t_fork		*left_fork;
	t_fork		*right_fork;
	int			meals_eaten;
	int			last_meal_date;
	
}	t_philosopher;

typedef struct	s_table
{
	int	philos_number;
	int	eat_time;
	int	sleep_time;
	int	think_time;
	int	time_to_die;
	int	meals_limit;
}	t_table;


int		input(int ac, char **av, t_table *table);



long	ft_atoi(const char *str, int *error);

#endif
