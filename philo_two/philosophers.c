/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:13 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/12 18:17:20 by pdemocri         ###   ########.fr       */
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
	g_philo[i]->take_2_forks++;
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
		if (i == 0)
			break ;
		if (g_philo[i - 1]->take_2_forks)
			break ;
		usleep(500);
	}
	if (i == 0)
		pthread_create(&g_params.check_death_thread, NULL, check_death, NULL);
	sem_wait(g_params.sem_start);
	sem_post(g_params.sem_start);
	g_params.queue++;
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
	while (i < params.num_of_philo)
	{
		pthread_create(g_thread[i], NULL, philo_action, &(g_philo[i]->num));
		i++;
	}
	pthread_join(g_params.check_death_thread, NULL);
	return (0);
}
