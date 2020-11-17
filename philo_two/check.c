/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:00 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 07:38:39 by pdemocri         ###   ########.fr       */
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
	char		num[32];
	char		buf[100];

	memset(buf, 0, 100);
	ft_itoa(buf, diff_time(g_params.start));
	buf[ft_strlen(buf)] = ' ';
	ft_itoa(num, i + 1);
	ft_strcat(buf, num);
	ft_strcat(buf, PRINT_DIED);
	write(1, buf, ft_strlen(buf));
	return (0);
}

void		*check_death(void *ptr)
{
	int			i;

	init_time(g_philo, g_params.num_of_philo);
	sem_post(g_params.sem_start);
	sem_post(g_params.sem_start);
	while (1)
	{
		i = -1;
		while (++i < g_params.num_of_philo)
		{
			if (!g_philo[i]->take_2_forks &&
				diff_time(g_philo[i]->last_eat) > g_params.time_to_die)
			{
				sem_wait(g_params.sem_print);
				return (died(i));
			}
		}
		if (g_params.must_eat &&
				g_params.full_eat_count == g_params.num_of_philo)
			return (NULL);
		usleep(500);
	}
	return (ptr);
}
