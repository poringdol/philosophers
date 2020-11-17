/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:11 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 06:27:43 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

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

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct	s_param
{
	int			num_of_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			must_eat;
	int			full_eat_count;
	int			time_inited;
	t_timeval	start;
	char		print_buf[100];
	t_mutex		print_mutex;
	pthread_t	check_death_thread;
	int			queue;
}				t_param;

typedef struct	s_philo
{
	t_timeval	last_eat;
	t_mutex		*fork1;
	t_mutex		*fork2;
	t_mutex		eat_mutex;
	int			num;
	int			eat_count;
}				t_philo;

int				check_input(int argc, char **argv);
void			*check_death(void *ptr);

int				print_error(char *error_message);
int				print_action(int i, char *action);

int				ft_isdigit(int ch);
int				ft_strlen(const char *str);
long			ft_atoi(const char *str);
void			ft_itoa(char *buf, long n);
char			*ft_strcat(char *dst, const char *src);

t_param			init_params(char **argv);
int				init_all(int n);
void			init_time(t_philo **philo, int n);
int				free_all(void);

int				philosophers(t_param params);
void			eating(int i);
long			diff_time(t_timeval last_eat);

t_param			g_params;
pthread_t		**g_thread;
t_mutex			**g_mutex;
t_philo			**g_philo;
#endif
