#include "header.h"

int 	check_input(int argc, char **argv)
{
	int			i;
	int			j;

	if (argc < PARAM_NUM - 1 || argc > PARAM_NUM)
	{
		write (2, WRONG_PARAM_NUMB, ft_strlen(WRONG_PARAM_NUMB));
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
				write (2, WRONG_PARAM, ft_strlen(WRONG_PARAM));
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int		check_full_eat(t_philo **philo, int n, int must_eat)
{
	if (!must_eat)
		return (0);
	while (n--)
	{
		if (philo[n]->eat_count < must_eat)
			return (0);
	}
	return (1);
}