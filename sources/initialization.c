#include "mini.h"

char	*get_key(char *s)
{
	char	*key;

	key = ft_strdupchr(s, '=');
	return (key);
}

char	*get_value(char *s)
{
	char	*value;
	int		i;

	i = 0;
	while (s[i] != '=')
		i++;
	if (s[i] != '=')
		return (NULL);
	value = ft_strdup(s + i + 1);
	return (value);
}

void	init_shell(int arg, char *argv[], char *envp[])
{
	int	arrLen;
	int	i;

	(void) arg;
	(void) argv;
	dup2(STDIN_FILENO, g_sh.fd[0]);
    dup2(STDOUT_FILENO, g_sh.fd[1]);
	arrLen = ft_2d_array_len(envp);
	g_sh.msEnvp = malloc(sizeof(char *) * arrLen);
	i = 0;
	while (i < arrLen)
	{
		g_sh.msEnvp[i] = ft_strdup(envp[i]);
		add_elem(&g_sh.listEnv, 
		new_env_elem(get_key(g_sh.msEnvp[i]), get_value(g_sh.msEnvp[i])));
		i++;
	}
	g_sh.msEnvp[i] = NULL;
	sort_list();
}
