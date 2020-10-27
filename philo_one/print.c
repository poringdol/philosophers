#include "header.h"

int		print_error(char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	return (1);
}

int		print_action(int i, char *action)
{
	char	num[32];

	pthread_mutex_lock(&(g_params.print_mutex));
	memset(g_params.print_buf, 0, 100);
	ft_itoa(g_params.print_buf, get_time(g_params.start));
	g_params.print_buf[ft_strlen(g_params.print_buf)] = ' ';
	ft_itoa(num, i + 1);
	ft_strcat(g_params.print_buf, num);
	ft_strcat(g_params.print_buf, action);
	write(1, g_params.print_buf, ft_strlen(g_params.print_buf));
	pthread_mutex_unlock(&(g_params.print_mutex));
	return (0);
}
