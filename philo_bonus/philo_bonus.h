/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/11 18:37:26 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h> 
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	t_table				*table;
	sem_t				**left_fork;
	sem_t				**right_fork;
	int					id;
	long long			last_meal_date;
	int					think_time;
	int					meals_eaten;
}	t_philosopher;

typedef struct s_table
{
	sem_t			**forks;
	sem_t			*end_semaphore;
	sem_t			*print_semaphore;
	t_philosopher	*philosophers;
	int				eat_time;
	int				sleep_time;
	int				end_dinner;
	int				time_to_die;
	int				meals_limit;
	int				philos_number;
	int				philos_done_eating;
}	t_table;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

void	clean_up(t_table *table);
int		init_semaphores(t_table *table);
int		init_philosophers(t_table *table);
long	ft_atoi(const char *str, int *error);
int		input(int ac, char **av, t_table *table);

long	get_time(void);
int		get_end_dinner(t_table *table);
int		get_start_dinner(t_table *table);
void	set_end_dinner(t_table *table, int value);
void	set_start_dinner(t_table *table, int value);
void	ft_usleep(long ms, t_philosopher *philosopher);
void	safe_print(t_philosopher *philosopher, char *msg);

#endif
