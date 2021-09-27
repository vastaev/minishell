/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:58 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/27 09:20:59 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*delete_from_list(t_env **lst, t_env *ptr)
{
	t_env	*elem;
	t_env	*curr;

	elem = NULL;
	curr = *lst;
	if (curr && curr == ptr)
	{
		elem = curr;
		*lst = elem->next;
		elem->next = NULL;
		return (elem);
	}
	while (curr->next)
	{
		if (curr->next == ptr)
		{
			elem = curr->next;
			curr->next = curr->next->next;
			elem->next = NULL;
			break ;
		}
		curr = curr->next;
	}	
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
			tmp = delete_from_list(&g_sh.listEnv, ptr);
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
