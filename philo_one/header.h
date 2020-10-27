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
// # define WRONG_THREAD_INIT "Threads initialization error\n"
// # define WRONG_MUTEX_INIT "Mutex initialization error\n"
// # define WRONG_PHILO_INIT "Philosophers initialization error\n"
# define INIT_ERROR "Initialization error\n"

# define PRINT_TAKE_FORK " has taken a fork\n"
# define PRINT_EAT " is eating\n"
# define PRINT_SLEEP " is sleeping\n"
# define PRINT_THINK " is thinking\n"
# define PRINT_DIED " died\n"

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
	t_timeval	start;
	char		print_buf[100];
	t_mutex		print_mutex;
}				t_param;

typedef struct	s_philo
{
	t_timeval	last_eat;
	t_mutex		*fork1;
	t_mutex		*fork2;
	int			eat_count;
	int			death_status;
	int			num;
}				t_philo;

int				check_input(int argc, char **argv);
int				check_full_eat(t_philo **philo, int n, int must_eat);

int				print_error(char *error_message);
int				print_action(int i, char *action);

int				ft_isdigit(int ch);
int				ft_strlen(const char *str);
long			ft_atoi(const char *str);
void			ft_itoa(char *buf, long n);
char   			 *ft_strcat(char *dst, const char *src);

int				eating(int i);
void			sleeping(int i);
void			thinking(int i);

t_param			init_params(char **argv);
int				init_all(int n);
// pthread_t		**init_thread(int n);
// t_mutex			**init_mutex(int n);
// t_philo			**init_philo(int n);
void			init_time(t_philo **philo, int n);
long			get_time(t_timeval last_eat);


int				join_thread(pthread_t **thread, int n);
int				destroy_mutex(t_mutex **mutex, int n);
int				detach_thread(pthread_t **thread, int n);

int				philosophers(t_param params);

t_param			g_params;
pthread_t		**g_thread;
t_mutex			**g_mutex;
t_philo			**g_philo;
int				g_death;

#endif
