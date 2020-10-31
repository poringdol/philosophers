#include "header.h"

int		eating(int i)
{
	t_timeval	current;

	pthread_mutex_lock(g_philo[i]->fork1);
	print_action(i, PRINT_TAKE_FORK);
	pthread_mutex_lock(g_philo[i]->fork2);
	print_action(i, PRINT_TAKE_FORK);
	gettimeofday(&current, NULL);
	g_philo[i]->last_eat = current;
	print_action(i, PRINT_EAT);
	usleep(g_params.time_to_eat);
	pthread_mutex_unlock(g_philo[i]->fork1);
	pthread_mutex_unlock(g_philo[i]->fork2);
	g_philo[i]->eat_count++;
	if (g_philo[i]->eat_count == g_params.must_eat)
		g_params.full_eat_count++;
	return (0);
}

void	*philo_action(void *n)
{
	const int		i = *(int *)n;

	while (1)
	{
		eating(i);
		print_action(i, PRINT_SLEEP);
		usleep(g_params.time_to_sleep);
		print_action(i, PRINT_THINK);
	}
	return (NULL);
}

int		philosophers(t_param params)
{
	int			i;
	pthread_t	check_d;

	i = 0;
	init_time(g_philo, g_params.num_of_philo);
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i += 2;
		usleep(50);
	}
	usleep(500);
	i = 1;
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i += 2;
		usleep(50);
	}
	pthread_create(&check_d, NULL, check_death, NULL);
	pthread_join(check_d, NULL);
	return (0);
}