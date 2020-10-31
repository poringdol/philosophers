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
}

void	*philo_action(void *n)
{
	const int		i = *(int *)n;

	pthread_detach(*(g_thread[i]));
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
	pthread_create(&check_d, NULL, check_death, NULL);
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i ++;
		usleep(200);
	}
	pthread_join(check_d, NULL);
	return (0);
}
