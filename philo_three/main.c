#include "header.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	if (check_input(argc - 1, &(argv[1])))
		return (1);
	g_params = init_params(argv);
	first_fork();
	// free_all();
	// sem_close(g_forks);
	return (0);
}
