#include "header.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	if (check_input(argc - 1, &(argv[1])))
		return (1);
	g_params = init_params(argv);
	if (init_all(g_params.num_of_philo))
		return (1);
	philosophers(g_params);
	free_all();
	sem_close(g_forks);
	// sem_unlink(SEMAPHOR);
	return (0);
}
