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