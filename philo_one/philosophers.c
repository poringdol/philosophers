#include "header.h"

void	*philo_action(void *n)
{
	// long			time_from_last_eat;
	const int		i = *(int *)n;

	while (1)
	{
		// time_from_last_eat = get_time(g_philo[i]->last_eat);
		// printf("%li\n", time_from_last_eat);

		if (eating(i))
			break;
		if (g_params.must_eat && g_params.full_eat_count == g_params.num_of_philo)
			break;
		sleeping(i);
		thinking(i);
	}
	return (NULL);
}

int		philosophers(t_param params)
{
	int i;

	i = 0;
	init_time(g_philo, g_params.num_of_philo);
	// while (i < params.num_of_philo)
	// {
	// 	philo_action(&(g_philo[i]->num));
	// 	i++;
	// }
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i += 2;
		usleep(10);
	}
	i = 1;
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i += 2;
		usleep(10);
	}
	while (1)
	{
		if (g_params.must_eat && g_params.full_eat_count == g_params.num_of_philo)
			return (0);
	}
	return (0);
}