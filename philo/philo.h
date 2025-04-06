/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/06 09:30:21 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef	struct s_table t_table;

typedef struct	s_philosopher
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					meals_eaten;
	long long			last_meal_date;
	t_table				*table;
}	t_philosopher;

typedef struct	s_table
{
	int				philos_number;
	int				eat_time;
	int				sleep_time;
	int				think_time;
	int				time_to_die;
	int				meals_limit;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
	int				end_dinner;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
}	t_table;


int		input(int ac, char **av, t_table *table);
int		init_forks(t_table *table);
int		init_philosophers(t_table *table);


long	ft_atoi(const char *str, int *error);

#endif
