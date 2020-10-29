#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>           /* For O_* constants */
# include <sys/stat.h>        /* For mode constants */
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

# define SEMAPHOR "/sem_name"

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
}				t_param;

typedef struct	s_philo
{
	t_timeval	last_eat;
	int			eat_count;
	int			num;
}				t_philo;

int				check_input(int argc, char **argv);
void			*check_death(void *ptr);

long			diff_time(t_timeval last_eat);

int				ft_isdigit(int ch);
int				ft_strlen(const char *str);
long			ft_atoi(const char *str);
void			ft_itoa(char *buf, long n);
char   			 *ft_strcat(char *dst, const char *src);

void			eating(int i);
void			sleeping(int i);
void			thinking(int i);

int				print_error(char *error_message);
int				print_action(int i, char *action);

t_param			init_params(char **argv);
int				init_all(int n);
void			init_time(t_philo **philo, int n);
void			free_all(void);

int				philosophers(t_param params);

t_param			g_params;
pthread_t		**g_thread;
t_philo			**g_philo;
sem_t			*g_forks;

#endif
