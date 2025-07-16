/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/07/16 18:37:32 by moaatik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
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
	sem_t			*print_semaphore;
	sem_t			*death_semaphore;
	t_philosopher	*philosophers;
	int				eat_time;
	int				sleep_time;
	int				time_to_die;
	int				meals_limit;
	int				philos_number;
	int				philos_done_eating;
}	t_table;

char	*ft_itoa(int n);
long	ft_atoi(const char *str, int *error);
char	*ft_strjoin(char const *s1, char const *s2);

void	clean_up(t_table *table);
int		init_philosophers(t_table *table);
void	clean_forks(sem_t	**forks, int size);
int		input(int ac, char **av, t_table *table);
void	wait_philos(pid_t *pids, int count, t_table *table);
int		init_semaphores(t_table *table, char *name, char *name1, int i);

long	get_time(void);
void	ft_usleep(long ms);
void	safe_print(t_philosopher *philosopher, char *msg);

#endif
