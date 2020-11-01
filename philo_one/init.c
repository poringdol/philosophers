/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:13 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/01 23:35:12 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_param	init_params(char **argv)
{
	t_param		params;

	memset(&params, 0, sizeof(t_param));
	params.num_of_philo = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]) * 1000;
	params.time_to_sleep = ft_atoi(argv[4]) * 1000;
	params.must_eat = argv[5] ? ft_atoi(argv[5]) : 0;
	pthread_mutex_init(&(params.print_mutex), NULL);
	return (params);
}

int		init_all(int n)
{
	int			i;

	if (!(g_thread = (pthread_t **)malloc(sizeof(pthread_t *) * n)) ||
		!(g_mutex = (t_mutex **)malloc(sizeof(t_mutex *) * n)) ||
		!(g_philo = (t_philo **)malloc(sizeof(t_philo *) * n)))
		return (print_error(INIT_ERROR));
	i = -1;
	while (++i < n)
	{
		if (!(g_thread[i] = (pthread_t *)malloc(sizeof(pthread_t))) ||
			!(g_mutex[i] = (t_mutex *)malloc(sizeof(t_mutex))) ||
			!(g_philo[i] = (t_philo *)malloc(sizeof(t_philo))) ||
			pthread_mutex_init(g_mutex[i], NULL))
			return (print_error(INIT_ERROR));
	}
	i = -1;
	while (++i < n)
	{
		memset(g_philo[i], 0, sizeof(t_philo));
		g_philo[i]->fork1 = i ? g_mutex[i - 1] : g_mutex[n - 1];
		g_philo[i]->fork2 = g_mutex[i];
		g_philo[i]->num = i;
	}
	return (0);
}

void	init_time(t_philo **philo, int n)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	while (n--)
		philo[n]->last_eat = time;
	g_params.start = time;
}

int		free_all(void)
{
	int		i;

	i = -1;
	while (++i < g_params.num_of_philo)
	{
		pthread_mutex_destroy(g_mutex[i]);
		pthread_mutex_destroy(&(g_philo[i]->eat_mutex));
		free(g_mutex[i]);
		free(g_thread[i]);
		free(g_philo[i]);
	}
	free(g_mutex);
	free(g_thread);
	free(g_philo);
	return (0);
}
