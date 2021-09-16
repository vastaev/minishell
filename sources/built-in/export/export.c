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

void	ft_export()
{
	int	i;

	i = 0;
	while (g_sh.msEnvp[i] != NULL)
	{
		add_elem(&g_sh.listEnv, new_env_elem(get_key(i), get_value(i))); 
		i++;
	}
	t_env *ptr;
	ptr = g_sh.listEnv;
	while (ptr->next)
	{
		printf("%s%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}