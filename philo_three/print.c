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
	write(1, buf, ft_strlen(buf));
	return (0);
}