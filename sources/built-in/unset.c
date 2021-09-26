#include "mini.h"

t_env	*delete_from_list(t_env **lst, char *arg)
{
	t_env	*elem;
	t_env	*curr;
	char	*tmp;

	elem = NULL;
	curr = *lst;
	tmp = get_key(arg);
	if (curr && ft_strcmp(curr->name, tmp) == 0)
	{
		elem = curr;
		*lst = elem->next;
		elem->next = NULL;
		free(tmp);
		return (elem);
	}
	while (curr->next)
	{
		if (ft_strcmp(curr->next->name, tmp) == 0)
		{
			elem = curr->next;
			curr->next = curr->next->next;
			elem->next = NULL;
			break ;
		}
		curr = curr->next;
	}
	free(tmp);
	return (elem);
}

int	ft_unset(t_cmdito *cmnd)
{
	int		i;
	t_env	*tmp;
	t_env	*ptr;

	if (cmnd->n_ar == 1)
		return (0);
	i = 1;
	while (cmnd->args[i])
	{
		ptr = find_env_key(cmnd->args[i]);
		if (!input_validation("unset", cmnd->args[i]) && ptr)
		{
			tmp = delete_from_list(&g_sh.listEnv, cmnd->args[i]);
			free(tmp->name);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			ft_2d_array_free(g_sh.msEnvp);
			g_sh.msEnvp = ft_list2array(g_sh.listEnv);
		}
		i++;
	}
	return (0);
}
