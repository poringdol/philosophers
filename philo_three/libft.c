#include "header.h"

int		ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (ch);
	return (0);
}

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	unsigned int	i;
	long			nb;
	long			nb_prev;
	int				sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb_prev = nb;
		nb = nb * 10 + str[i] - '0';
		i++;
		if (nb_prev > nb)
			return (sign == 1 ? -1 : 0);
	}
	nb *= sign;
	return (nb);
}

void	ft_itoa(char *buf, long n)
{
	unsigned long	len;
	unsigned long	tmp;

	if (!n)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return ;
	}
	tmp = n;
	len = 1;
	while ((n /= 10))
		len++;
	buf[len] = '\0';
	while (tmp)
	{
		buf[--len] = tmp % 10 + '0';
		tmp /= 10;
	}
}

char    *ft_strcat(char *dst, const char *src)
{
        int i;
        int j;

        i = 0;
        j = 0;
        while (dst[i])
                i++;
        while (src[j])
                dst[i++] = src[j++];
        dst[i] = '\0';
        return (dst);
}
