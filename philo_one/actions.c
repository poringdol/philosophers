#include "header.h"

int		eating(int i)
{
	t_timeval	current;
	// long		time_from_last_eat;

	pthread_mutex_lock(g_philo[i]->fork1);
	print_action(i, PRINT_TAKE_FORK);
	pthread_mutex_lock(g_philo[i]->fork2);
	print_action(i, PRINT_TAKE_FORK);
	// time_from_last_eat = get_time(g_philo[i]->last_eat);
	// if (time_from_last_eat > g_params.time_to_die)
	// 	return (print_action(i, PRINT_DIED) + 1);
	gettimeofday(&current, NULL);
	g_philo[i]->last_eat = current;
	print_action(i, PRINT_EAT);
	usleep(g_params.time_to_eat);
	g_philo[i]->eat_count++;
	if (g_philo[i]->eat_count == g_params.must_eat)
		g_params.full_eat_count++;
	pthread_mutex_unlock(g_philo[i]->fork1);
	pthread_mutex_unlock(g_philo[i]->fork2);
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

