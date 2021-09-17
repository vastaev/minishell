#include "mini.h"

char	*get_key(int index)
{
	char	*key;

	key = ft_strdupchr(g_sh.msEnvp[index], '=');
	return (key);
}

char	*get_value(int index)
{
	char	*value;
	int		i;

	i = 0;
	while (g_sh.msEnvp[index][i] != '=')
		i++;
	value = ft_strdup(g_sh.msEnvp[index] + i + 1);
	return (value);
}

void	init_shell(char *envp[])
{
	int	arrLen;
	int	i;

	dup2(STDIN_FILENO, g_sh.fd[0]);
    dup2(STDOUT_FILENO, g_sh.fd[1]);
	arrLen = ft_2d_array_len(envp);
	g_sh.msEnvp = malloc(sizeof(char *) * arrLen + 1);
	i = 0;
	while (i < arrLen)
	{
		g_sh.msEnvp[i] = envp[i];
		add_elem(&g_sh.listEnv, new_env_elem(get_key(i), get_value(i)));
		i++;
	}
	g_sh.msEnvp[i] = NULL;
}
