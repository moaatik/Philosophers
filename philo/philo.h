/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/04 17:47:53 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>

typedef struct	s_philosopher
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					meals_eaten;
	int					last_meal_date;
	int					eat_time;
	int					sleep_time;
	int					think_time;
	int					time_to_die;
	int					meals_limit;
	
}	t_philosopher;

typedef struct	s_table
{
	int				philos_number;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
}	t_table;


int		input(int ac, char **av, t_table *table);
int		init_forks(t_table *table);
int		init_philosophers(t_table *table);


long	ft_atoi(const char *str, int *error);

#endif
