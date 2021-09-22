#include "mini.h"

void	delete_from_list(char *arg)
{
	t_env	*ptr;
	t_env	*tmp;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	ptr = g_sh.listEnv;
	while (ptr->next)
	{
		if (ft_strncmp(ptr->next->name, arg, i) == 0)
		{
			tmp = ptr;
			ptr->next = ptr->next->next;
			free(tmp->next->name);
			if (tmp->next->value)
				free(tmp->next->value);
			free(tmp->next);
			tmp->next = NULL;
			return ;
		}
		ptr = ptr->next;
	}
}

int	ft_unset(t_cmdito *cmnd)
{
	int		i;
	t_env	*ptr;

	if (cmnd->n_ar == 1)
		return (0);
	i = 1;
	while (cmnd->args[i])
	{
		if (input_validation("unset", cmnd->args[i]) == 0)
		{
			delete_from_list(cmnd->args[i]);
			ft_2d_array_free(g_sh.msEnvp);
			g_sh.msEnvp = ft_list2array(g_sh.listEnv);	
		}
		i++;
	}
	return (0);
}