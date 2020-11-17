/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:07 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 02:53:58 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <errno.h>
#include <stdio.h>

t_param		init_params(char **argv)
{
	t_param		params;

	memset(&params, 0, sizeof(t_param));
	params.num_of_philo = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]) * 1000;
	params.time_to_sleep = ft_atoi(argv[4]) * 1000;
	params.must_eat = argv[5] ? ft_atoi(argv[5]) : 0;
	return (params);
}

int			init_all(int n)
{
	int			i;

	if (!(g_thread = (pthread_t **)malloc(sizeof(pthread_t *) * n)) ||
		!(g_philo = (t_philo **)malloc(sizeof(t_philo *) * n)))
		return (print_error(INIT_ERROR));
	i = -1;
	while (++i < n)
	{
		if (!(g_thread[i] = (pthread_t *)malloc(sizeof(pthread_t))) ||
			!(g_philo[i] = (t_philo *)malloc(sizeof(t_philo))))
			return (print_error(INIT_ERROR));
	}
	i = -1;
	while (++i < n)
	{
		memset(g_philo[i], 0, sizeof(t_philo));
		g_philo[i]->num = i;
	}
	init_semaphors();
	return (0);
}

void		init_time(t_philo **philo, int n)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	while (n--)
		philo[n]->last_eat = time;
	g_params.start = time;
}

int			init_semaphors(void)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_START);
	if ((g_forks = sem_open(SEM_FORK, O_CREAT, 0666, g_params.num_of_philo)) ==
					SEM_FAILED ||
		((g_params.sem_start = sem_open(SEM_START, O_CREAT, 0666, 0)) ==
					SEM_FAILED))
		return (print_error(INIT_ERROR));
	return (0);
}

void		free_all(void)
{
	int		i;

	i = -1;
	while (++i < g_params.num_of_philo)
	{
		free(g_thread[i]);
		free(g_philo[i]);
	}
	free(g_thread);
	free(g_philo);
}
