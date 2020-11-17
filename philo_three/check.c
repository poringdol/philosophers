/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:29 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 08:29:33 by pdemocri         ###   ########.fr       */
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

void		*check_death(void *philo_i)
{
	const int	i = *(int *)philo_i;

	while (!g_philo[i]->death_status)
	{
		sem_wait(g_sem_print);
		if (!g_philo[i]->take_2_forks &&
			diff_time(g_philo[i]->last_eat) > g_params.time_to_die)
		{
			g_philo[i]->death_status++;
			died(i);
			exit(0);
		}
		sem_post(g_sem_print);
	}
	if (g_params.must_eat && g_params.full_eat_count == g_params.num_of_philo)
		sem_post(g_sem_full_eat);
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
