/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:08:08 by pdemocri          #+#    #+#             */
/*   Updated: 2020/10/31 17:08:09 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int		destroy_mutex(t_mutex **mutex, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		pthread_mutex_destroy(mutex[i]);
		free(mutex[i]);
	}
	free(mutex);
	return (0);
}

int		detach_thread(pthread_t **thread, int n)
{
	int		i;

	i = -1;
	while (++i < n)
		pthread_detach((*thread)[i]);
	return (0);
}
