/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:23 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 06:15:53 by pdemocri         ###   ########.fr       */
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
	pthread_mutex_lock(g_philo[i]->fork1);
	pthread_mutex_lock(g_philo[i]->fork2);
	pthread_mutex_lock(&(g_philo[i]->eat_mutex));
	print_action(i, PRINT_TAKE_FORK);
	print_action(i, PRINT_TAKE_FORK);
	gettimeofday(&(g_philo[i]->last_eat), NULL);
	print_action(i, PRINT_EAT);
	pthread_mutex_unlock(&(g_philo[i]->eat_mutex));
	usleep(g_params.time_to_eat);
	pthread_mutex_unlock(g_philo[i]->fork1);
	pthread_mutex_unlock(g_philo[i]->fork2);
	g_philo[i]->eat_count++;
	if (g_philo[i]->eat_count == g_params.must_eat)
		g_params.full_eat_count++;
}

void	*philo_action(void *n)
{
	const int		i = *(int *)n;

	pthread_detach(*g_thread[i]);
	while (1)
	{
		if (i == g_params.queue)
			break ;
		usleep(500);
	}
	g_params.queue = ((i + 2) < g_params.num_of_philo) ?
					(g_params.queue + 2) : 1;
	if (i == 0)
		init_time(g_philo, g_params.num_of_philo);
	while (1)
	{
		eating(i);
		print_action(i, PRINT_SLEEP);
		usleep(g_params.time_to_sleep + 500);
		print_action(i, PRINT_THINK);
	}
	return (NULL);
}

int		philosophers(t_param params)
{
	int			i;

	i = 0;
	pthread_create(&g_params.check_death_thread, NULL, check_death, NULL);
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i++;
	}
	pthread_join(g_params.check_death_thread, NULL);
	return (0);
}
