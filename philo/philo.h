/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/04/11 16:45:12 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int					id;
	t_table				*table;
	int					think_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					meals_eaten;
	long long			last_meal_date;
}	t_philosopher;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	int				eat_time;
	pthread_mutex_t	end_mutex;
	int				sleep_time;
	int				end_dinner;
	int				time_to_die;
	pthread_mutex_t	print_mutex;
	int				meals_limit;
	int				philos_number;
	t_philosopher	*philosophers;
	int				philos_done_eating;
}	t_table;

void	clean_up(t_table *table);
int		init_forks(t_table *table);
int		init_philosophers(t_table *table);
int		input(int ac, char **av, t_table *table);

long	get_time(void);
void	ft_usleep(long ms);
int		get_end_dinner(t_table *table);
void	set_end_dinner(t_table *table, int value);
void	safe_print(t_philosopher *philosopher, char *msg);

long	ft_atoi(const char *str, int *error);

#endif
