/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:29 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 02:18:22 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_input(int argc, char **argv)
{
	int			i;
	int			j;

	if (argc < PARAM_NUM - 1 || argc > PARAM_NUM)
	{
		write(2, WRONG_PARAM_NUMB, ft_strlen(WRONG_PARAM_NUMB));
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(2, WRONG_PARAM, ft_strlen(WRONG_PARAM));
				return (1);
			}
			j++;
		}
	}
	return (0);
}

void	*check_death(void *philo_i)
{
	const int	i = *(int *)philo_i;
	t_timeval	cuerrent_time;

	gettimeofday(&cuerrent_time, NULL);
	while (!g_philo[i]->death_status)
	{
		sem_wait(g_sem_death);
		if (diff_time(g_philo[i]->last_eat) > g_params.time_to_die)
		{
			g_philo[i]->death_status++;
			print_action(i, PRINT_DIED);
			exit(0);
		}
		sem_post(g_sem_death);
	}
	if (g_params.must_eat && g_params.full_eat_count == g_params.num_of_philo)
		sem_post(g_sem_full_eat);
	usleep(1000);
	exit(0);
}

int		check_full_eat(int n)
{
	int		i;

	i = -1;
	while (++i < n)
		sem_wait(g_sem_full_eat);
	exit(0);
}
