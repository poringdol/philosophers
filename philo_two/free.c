/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:02 by pdemocri          #+#    #+#             */
/*   Updated: 2020/10/31 17:15:57 by pdemocri         ###   ########.fr       */
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
