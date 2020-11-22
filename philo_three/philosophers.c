/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:44 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/20 15:36:49 by pdemocri         ###   ########.fr       */
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
	sem_wait(g_sem_forks);
	print_action(i, PRINT_TAKE_FORK);
	sem_wait(g_sem_forks);
	g_philo[i]->take_2_forks++;
	sem_post(g_sem_start);
	print_action(i, PRINT_TAKE_FORK);
	gettimeofday(&(g_philo[i]->last_eat), NULL);
	print_action(i, PRINT_EAT);
	usleep(g_params.time_to_eat);
	g_philo[i]->take_2_forks = 0;
	sem_post(g_sem_forks);
	sem_post(g_sem_forks);
	g_philo[i]->eat_count++;
	if (g_philo[i]->eat_count == g_params.must_eat)
		sem_post(g_sem_full_eat);
}

int		philo_action(void *n)
{
	const int	i = *(int *)n;
	pthread_t	check_d;

	pthread_create(&check_d, NULL, check_death, n);
	sem_wait(g_sem_start);
	sem_post(g_sem_start);
	while (!(g_philo[i]->death_status))
	{
		eating(i);
		print_action(i, PRINT_SLEEP);
		usleep(g_params.time_to_sleep);
		print_action(i, PRINT_THINK);
	}
	pthread_join(check_d, NULL);
	exit(0);
}

int		philosophers(t_param params)
{
	int			i;
	pid_t		pid_check;
	pid_t		pid_action;

	i = -1;
	init_all(g_params.num_of_philo);
	init_time(g_philo, g_params.num_of_philo);
	pid_check = fork();
	if (pid_check == 0)
		check_full_eat(g_params.num_of_philo);
	else
	{
		while (++i < params.num_of_philo)
		{
			pid_action = fork();
			g_pid[i] = pid_action;
			if (pid_action == 0)
				philo_action(&(g_philo[i]->num));
			else if (pid_action > 0)
				usleep(500);
		}
	}
	waitpid(-1, NULL, 0);
	kill_all();
	exit(0);
}

int		first_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		philosophers(g_params);
	else if (pid > 0)
		waitpid(-1, NULL, 0);
	else
		return (1);
	return (0);
}
