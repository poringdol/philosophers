/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:00 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/12 03:08:10 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			check_input(int argc, char **argv)
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

static void	*died(int i)
{
	pthread_mutex_lock(&(g_params.eat_mutex));
	g_params.death_status = 1;
	print_action(i, PRINT_DIED);
	return (NULL);
}

void		*check_death(void *ptr)
{
	int			i;
	t_timeval	cuerrent_time;
	long		time;

	init_time(g_philo, g_params.num_of_philo);
	while (1)
	{
		i = -1;
		gettimeofday(&cuerrent_time, NULL);
		while (++i < g_params.num_of_philo)
		{
			time = diff_time(g_philo[i]->last_eat);
			if (time > g_params.time_to_die)
				return (died(i));
		}
		if (g_params.must_eat &&
				g_params.full_eat_count == g_params.num_of_philo)
			return (NULL);
		usleep(100);
	}
	return (ptr);
}
