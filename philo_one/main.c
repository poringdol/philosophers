#include "header.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	if (check_input(argc - 1, &(argv[1])))
		return (1);
	g_params = init_params(argv);
	if (init_all(g_params.num_of_philo))
		return (1);
	init_time(g_philo, g_params.num_of_philo);
	philosophers(g_params);
	destroy_mutex(g_mutex, g_params.num_of_philo);
	return (0);
}