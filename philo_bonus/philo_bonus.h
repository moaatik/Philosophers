/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaatik <moaatik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:03:31 by moaatik           #+#    #+#             */
/*   Updated: 2025/08/02 07:35:50 by moaatik          ###   ########.fr       */
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
	long long			last_meal_date;
	sem_t				*meal_semaphore;
	int					id;
	int					meals_eaten;
	int					is_eating;
}	t_philosopher;

typedef struct s_table
{
	t_philosopher	*philosophers;
	sem_t			*forks;
	sem_t			*print_semaphore;
	long			start_time;
	int				eat_time;
	int				sleep_time;
	int				time_to_die;
	int				meals_limit;
	int				philos_number;
	int				usleep_time;
	int				philos_done_eating;
}	t_table;

char	*ft_itoa(int n);
int		ft_strlen(const char *s);
long	ft_atoi(const char *str, int *error);
char	*ft_strjoin_3(char *s1, char *s2, char *s3);

void	clean_up(t_table *table);
int		init_semaphores(t_table *table);
int		init_philosophers(t_table *table);
int		input(int ac, char **av, t_table *table);
void	kill_prev_philos(pid_t *pids, int count);
void	wait_philos(pid_t *pids, int count, t_table *table);

long	get_time(t_table *table);
void	ft_usleep(long ms, t_table *table);
void	safe_print(t_philosopher *philosopher, char *msg);

#endif
