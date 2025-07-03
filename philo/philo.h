/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/01 20:35:15 by moaatik          ###   ########.fr       */
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
	t_table				*table;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					id;
	long long			last_meal_date;
	int					think_time;
	int					meals_eaten;
}	t_philosopher;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	print_mutex;
	t_philosopher	*philosophers;
	int				eat_time;
	int				sleep_time;
	int				end_dinner;
	int				start_dinner;
	int				time_to_die;
	int				meals_limit;
	int				philos_number;
	int				philos_done_eating;
}	t_table;

void	clean_up(t_table *table);
int		init_mutexes(t_table *table);
int		init_philosophers(t_table *table);
long	ft_atoi(const char *str, int *error);
int		input(int ac, char **av, t_table *table);

long	get_time(void);
int		get_end_dinner(t_table *table);
int		get_start_dinner(t_table *table);
void	join_threads(pthread_t	*threads, int i);
void	set_end_dinner(t_table *table, int value);
void	set_start_dinner(t_table *table, int value);
void	ft_usleep(long ms, t_philosopher *philosopher);
void	safe_print(t_philosopher *philosopher, char *msg);

#endif
