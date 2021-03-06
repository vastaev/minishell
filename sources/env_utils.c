/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:15:40 by uterese           #+#    #+#             */
/*   Updated: 2021/09/28 02:16:59 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_getenv(char *name)
{
	t_env	*ale;

	ale = g_sh.listenv;
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
		if (ale->value == NULL)
		{
			ale = ale->next;
			continue ;
		}
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
		if (iter->value == NULL)
		{
			iter = iter->next;
			continue ;
		}
		ale[0] = ft_strjoin(iter->name, "=");
		ale[1] = ft_strjoin(ale[0], iter->value);
		new[i++] = ft_strdup(ale[1]);
		free(ale[0]);
		free(ale[1]);
		iter = iter->next;
	}
	return (new);
}
