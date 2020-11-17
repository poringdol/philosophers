/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:05 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 07:07:21 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define PARAM_NUM 5

# define WRONG_PARAM "Invalid parameter. Only numeric parameters are possible\n"
# define WRONG_PARAM_NUMB "There must be 4 or 5 parameters\n"
# define INIT_ERROR "Initialization error\n"

# define PRINT_TAKE_FORK " has taken a fork\n"
# define PRINT_EAT " is eating\n"
# define PRINT_SLEEP " is sleeping\n"
# define PRINT_THINK " is thinking\n"
# define PRINT_DIED " died\n"
# define PRINT_FULL "All philosophers are full\n"

# define SEM_FORK "/sem_fork"
# define SEM_START "/sem_start"
# define SEM_PRINT "/sem_print"

typedef struct timeval	t_timeval;

typedef struct	s_param
{
	int			num_of_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			must_eat;
	int			full_eat_count;
	t_timeval	start;
	sem_t		*sem_start;
	sem_t		*sem_print;
	pthread_t	check_death_thread;
}				t_param;

typedef struct	s_philo
{
	t_timeval	last_eat;
	int			eat_count;
	int			num;
	int			take_2_forks;
}				t_philo;

int				check_input(int argc, char **argv);
void			*check_death(void *ptr);

long			diff_time(t_timeval last_eat);

int				ft_isdigit(int ch);
int				ft_strlen(const char *str);
long			ft_atoi(const char *str);
void			ft_itoa(char *buf, long n);
char			*ft_strcat(char *dst, const char *src);

int				print_error(char *error_message);
int				print_action(int i, char *action);

t_param			init_params(char **argv);
int				init_all(int n);
void			init_time(t_philo **philo, int n);
int				init_semaphors(void);
void			free_all(void);

int				philosophers(t_param params);
void			eating(int i);

t_param			g_params;
pthread_t		**g_thread;
t_philo			**g_philo;
sem_t			*g_forks;

#endif
