#include "mini.h"

void	init_shell(char *envp[])
{
	int	arrLen;
	int	i;


	arrLen = ft_2d_array_len(envp);
	g_sh.msEnvp = malloc(sizeof(char *) * (arrLen + 1));
	i = 0;
	while (i < arrLen)
	{
		g_sh.msEnvp[i] = envp[i];
		i++;
	}
	g_sh.msEnvp[i] = NULL;
}
