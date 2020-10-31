/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:31 by pdemocri          #+#    #+#             */
/*   Updated: 2020/10/31 17:08:31 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_all(void)
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

int		join_thread(pthread_t **thread, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		pthread_join((*thread)[i], NULL);
		free(thread[i]);
	}
	free(thread);
	return (0);
}

int		kill_all(void)
{
	int		i;

	i = -1;
	while (++i < g_params.num_of_philo)
		kill(g_pid[i], SIGKILL);
	return (0);
}
