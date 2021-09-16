#include "mini.h"

void	ft_env()
{
	int	i;

	i = 0;
	while (g_sh.msEnvp[i] != NULL)
	{
		printf("%s\n", g_sh.msEnvp[i]);
		i++;
	}
}