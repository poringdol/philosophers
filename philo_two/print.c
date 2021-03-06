/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:09:15 by pdemocri          #+#    #+#             */
/*   Updated: 2020/11/17 07:09:34 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		print_error(char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	return (1);
}

int		print_action(int i, char *action)
{
	char	num[32];
	char	buf[100];

	memset(buf, 0, 100);
	ft_itoa(buf, diff_time(g_params.start));
	buf[ft_strlen(buf)] = ' ';
	ft_itoa(num, i + 1);
	ft_strcat(buf, num);
	ft_strcat(buf, action);
	sem_wait(g_params.sem_print);
	write(1, buf, ft_strlen(buf));
	sem_post(g_params.sem_print);
	return (0);
}
