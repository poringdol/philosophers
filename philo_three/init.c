/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:34 by pdemocri          #+#    #+#             */
/*   Updated: 2020/10/31 17:25:26 by pdemocri         ###   ########.fr       */
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

	if (!(g_philo = (t_philo **)malloc(sizeof(t_philo *) * n)))
		return (print_error(INIT_ERROR));
	if (!(g_pid = (pid_t *)malloc(sizeof(pid_t) * n)))
		return (print_error(INIT_ERROR));
	i = -1;
	while (++i < n)
	{
		if (!(g_philo[i] = (t_philo *)malloc(sizeof(t_philo))))
			return (print_error(INIT_ERROR));
		memset(g_philo[i], 0, sizeof(t_philo));
		g_philo[i]->num = i;
	}
	i = -1;
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_FULL_EAT);
	if (((g_sem_forks = sem_open(SEM_FORK, O_CREAT, 0666, n))
					== SEM_FAILED) ||
		((g_sem_death = sem_open(SEM_DEATH, O_CREAT, 0666, 1)) == SEM_FAILED) ||
		((g_sem_full_eat = sem_open(SEM_FULL_EAT, O_CREAT, 0666, 0))
						== SEM_FAILED))
		return (print_error(INIT_ERROR));
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

long		diff_time(t_timeval last_eat)
{
	t_timeval	current_time;
	t_timeval	sub;

	gettimeofday(&current_time, NULL);
	timersub(&current_time, &last_eat, &sub);
	return (sub.tv_sec * 1000 + sub.tv_usec / 1000);
}
