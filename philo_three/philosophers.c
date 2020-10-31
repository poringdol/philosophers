#include "header.h"

void	eating(int i)
{
	t_timeval	current;

	sem_wait(g_sem_forks);
	print_action(i, PRINT_TAKE_FORK);
	sem_wait(g_sem_forks);
	print_action(i, PRINT_TAKE_FORK);
	gettimeofday(&current, NULL);
	// sem_post(g_sem_death);
	g_philo[i]->last_eat = current;
	print_action(i, PRINT_EAT);
	// sem_wait(g_sem_death);
	usleep(g_params.time_to_eat);
	sem_post(g_sem_forks);
	sem_post(g_sem_forks);
	g_philo[i]->eat_count++;
	if (g_philo[i]->eat_count == g_params.must_eat)
		sem_post(g_sem_full_eat);
}

int		philo_action(void *n)
{
	const int	i = *(int *)n;
	pthread_t	check_d;
	// pthread_t		check_f_e;

	pthread_create(&check_d, NULL, check_death, n);
	// pthread_create(&check_d, NULL, check_full_eat, NULL);
	while (!(g_philo[i]->death_status))
	{
		eating(i);
		print_action(i, PRINT_SLEEP);
		usleep(g_params.time_to_sleep);
		print_action(i, PRINT_THINK);
	}
	pthread_join(check_d, NULL);
	// pthread_join(check_f_e, NULL);
	exit(0);
}

int		philosophers(t_param params)
{
	int			i;
	pid_t		pid_check;
	pid_t		pid_action;

	i = -1;
	init_all(g_params.num_of_philo);
	init_time(g_philo, g_params.num_of_philo);
	pid_check = fork();
	if (pid_check == 0)
		check_full_eat(g_params.num_of_philo);
	// else
	// {
	while (++i < params.num_of_philo)
	{
		pid_action = fork();
		g_pid[i] = pid_action;
		if (pid_action == 0)
			philo_action(&(g_philo[i]->num));
		else if (pid_action > 0)
			usleep(500);
		else
			break;
	}
	// }
	waitpid(-1, NULL, 0);
	kill_all();
	
	exit(0);
}

int		first_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		philosophers(g_params);
	else if (pid > 0)
		waitpid(-1, NULL, 0);
	else
		return (1);
	return (0);
}
