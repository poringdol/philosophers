#include "header.h"

void	eating(int i)
{
	t_timeval	current;

	sem_wait(g_forks);
	print_action(i, PRINT_TAKE_FORK);
	sem_wait(g_forks);
	print_action(i, PRINT_TAKE_FORK);
	gettimeofday(&current, NULL);
	g_philo[i]->last_eat = current;
	
	print_action(i, PRINT_EAT);
	usleep(g_params.time_to_eat);
	g_philo[i]->eat_count++;
	if (g_philo[i]->eat_count == g_params.must_eat)
		g_params.full_eat_count++;
	sem_post(g_forks);
	sem_post(g_forks);
	return (0);
}

void	sleeping(int i)
{
	print_action(i, PRINT_SLEEP);
	usleep(g_params.time_to_sleep);
}

void	thinking(int i)
{
	print_action(i, PRINT_THINK);
}

