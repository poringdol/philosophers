#include "header.h"

void	*check_death(void *ptr)
{
	int			i;
	t_timeval	cuerrent_time;

	while (1)
	{
		i = -1;
		gettimeofday(&cuerrent_time, NULL);
		while (++i < g_params.num_of_philo)
		{
			if (get_time(g_philo[i]->last_eat) > g_params.time_to_die)
			{
				print_action(i, PRINT_DIED);
				return (ptr);
			}
		}
		if (g_death || 
			(g_params.must_eat && g_params.full_eat_count == g_params.num_of_philo))
			return (ptr);
		usleep(500);
	}
	return (ptr);
}

void	*philo_action(void *n)
{
	const int		i = *(int *)n;

	while (1)
	{
		eating(i);
		// if (eating(i))
		// {
		// 	g_death = 1;
		// 	break;
		// }
		sleeping(i);
		thinking(i);
	}
	return (NULL);
}

int		philosophers(t_param params)
{
	int			i;
	pthread_t	check_d;
	// t_timeval	cuerrent_time;

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
		usleep(50);
	}
	i = 1;
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i += 2;
		usleep(50);
	}
	// while (1)
	// {
	// 	i = -1;
	// 	gettimeofday(&cuerrent_time, NULL);
	// 	while (++i)
	// 	{
	// 		if (get_time(g_philo[i]->last_eat) > g_params.must_eat)
	// 			return (print_action(i, PRINT_DIED));
	// 	}
	// 	if (g_death || 
	// 		(g_params.must_eat && g_params.full_eat_count == g_params.num_of_philo))
	// 		return (0);
	// }

	// join_thread(g_thread, g_params.num_of_philo);
	pthread_create(&check_d, NULL, check_death, NULL);
	pthread_join(check_d, NULL);
	return (0);
}