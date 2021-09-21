#include "mini.h"

char    *ft_getenv(char *name)
{
    t_env   *ale;

    ale = g_sh.listEnv;
    while (ale)
    {
        if (!ft_strncmp(name, ale->name, ft_strlen(ale->name) + 1))
            return (ale->value);
        ale = ale->next;
    }
    return (0);
}

static int	ft_getlistlen(t_env *env)
{
	t_env	*ale;
	int		cont;

	cont = 0;
	ale = env;
	while (ale)
	{
		cont++;
		ale = ale->next;
	}
	return (cont);
}

char	**ft_list2array(t_env *env)
{
	char	**new;
	t_env	*iter;
	char	*ale[2];
	int		i;

	i = 0;
	new = ft_calloc(ft_getlistlen(env) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	iter = env;
	while (iter)
	{
		ale[0] = ft_strjoin(iter->name, "=");
		ale[1] = ft_strjoin(ale[0], iter->value);
		new[i] = ft_strdup(ale[1]);
		if (ale[0])
			free(ale[0]);
		if (ale[1])
			free(ale[1]);
		i++;
		iter = iter->next;
	}
	return (new);
}