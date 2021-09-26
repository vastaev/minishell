#include "mini.h"

void	delete_from_list(t_env **lst, char *arg)
{
	// t_env	*elem;
	// t_env	*curr;

	// elem = NULL;
	// curr = *lst;
	// if (curr && !ft_strncmp(curr->name, arg, ft_keylen(arg)))
	// {
	// 	elem = curr;
	// 	*lst = elem->next;
	// 	elem->next = NULL;
	// }
	// while (curr && curr->next)
	// {
	// 	if (!ft_strncmp(curr->next->name, arg, ft_keylen(arg)))
	// 	{
	// 		elem = curr->next;
	// 		curr->next = curr->next->next;
	// 		elem->next = NULL;
	// 		break ;
	// 	}
	// 	curr = curr->next;
	// }
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
			tmp = ptr->next;
			ptr->next = tmp->next;
			tmp->next = NULL;
			free(tmp->name);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
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
			delete_from_list(&g_sh.listEnv, cmnd->args[i]);
			ft_2d_array_free(g_sh.msEnvp);
			g_sh.msEnvp = ft_list2array(g_sh.listEnv);	
		}
		i++;
	}
	return (0);
}