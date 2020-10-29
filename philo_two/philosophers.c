#include "header.h"

void	*philo_action(void *n)
{
	const int		i = *(int *)n;

	while (1)
	{
		eating(i);
		sleeping(i);
		thinking(i);
	}
	return (NULL);
}

int		philosophers(t_param params)
{
	int			i;
	pthread_t	check_d;

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
		i ++;
		usleep(200);
	}
	pthread_create(&check_d, NULL, check_death, NULL);
	pthread_join(check_d, NULL);
	return (0);
}