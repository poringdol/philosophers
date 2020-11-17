/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:00 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 06:42:34 by pdemocri         ###   ########.fr       */
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
	char	num[32];

	memset(g_params.print_buf, 0, 100);
	ft_itoa(g_params.print_buf, diff_time(g_params.start));
	g_params.print_buf[ft_strlen(g_params.print_buf)] = ' ';
	ft_itoa(num, i + 1);
	ft_strcat(g_params.print_buf, num);
	ft_strcat(g_params.print_buf, PRINT_DIED);
	write(1, g_params.print_buf, ft_strlen(g_params.print_buf));
	return (NULL);
}

void		*check_death(void *ptr)
{
	int			i;

	while (!g_params.time_inited)
		;
	while (1)
	{
		i = -1;
		while (++i < g_params.num_of_philo)
		{
			pthread_mutex_lock(&(g_philo[i]->eat_mutex));
			if (diff_time(g_philo[i]->last_eat) > g_params.time_to_die)
			{
				pthread_mutex_lock(&(g_params.print_mutex));
				return (died(i));
			}
			pthread_mutex_unlock(&(g_philo[i]->eat_mutex));
		}
		if (g_params.must_eat &&
				g_params.full_eat_count == g_params.num_of_philo)
			return (NULL);
	}
	return (ptr);
}
