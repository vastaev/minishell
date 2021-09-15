#include "mini.h"

void	init_shell(char *envp[])
{
	int	arrLen;
	int	i;

	dup2(STDIN_FILENO, g_sh.fd[0]);
    dup2(STDOUT_FILENO, g_sh.fd[1]);
	arrLen = ft_2d_array_len(envp);
	g_sh.msEnvp = malloc(sizeof(char *) * (arrLen));
	i = 0;
	while (i < arrLen)
	{
		g_sh.msEnvp[i] = envp[i];
		i++;
	}
	g_sh.msEnvp[i] = NULL;
	change_env_field("SHLVL=", "SHLVL=2");
}
