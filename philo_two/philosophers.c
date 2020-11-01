/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:13 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/02 00:53:32 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	diff_time(t_timeval last_eat)
{
	t_timeval	current_time;
	t_timeval	sub;

	gettimeofday(&current_time, NULL);
	timersub(&current_time, &last_eat, &sub);
	return (sub.tv_sec * 1000 + sub.tv_usec / 1000);
}

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
	sem_post(g_forks);
	sem_post(g_forks);
	g_philo[i]->eat_count++;
	if (g_philo[i]->eat_count == g_params.must_eat)
		g_params.full_eat_count++;
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
		i++;
		usleep(500);
	}
	pthread_join(check_d, NULL);
	return (0);
}
