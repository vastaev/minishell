/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:42 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/28 02:17:11 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	data_swap(t_env *ptr, t_env *ptr2, t_env *tmp)
{
	tmp->name = ptr->name;
	tmp->value = ptr->value;
	ptr->name = ptr2->name;
	ptr->value = ptr2->value;
	ptr2->name = tmp->name;
	ptr2->value = tmp->value;
}

void	sort_list(void)
{
	int		did_swap;
	t_env	*ptr;
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	did_swap = 1;
	while (did_swap)
	{
		did_swap = 0;
		ptr = g_sh.listenv;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				data_swap(ptr, ptr->next, tmp);
				did_swap = 1;
			}
			ptr = ptr->next;
		}
	}
	free(tmp);
}

t_env	*find_env_key(char *arg)
{
	t_env	*ptr;
	char	*tmp_key;

	tmp_key = get_key(arg);
	if (!tmp_key)
		return (NULL);
	ptr = g_sh.listenv;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, tmp_key) == 0)
		{
			free(tmp_key);
			return (ptr);
		}
		ptr = ptr->next;
	}
	free(tmp_key);
	return (NULL);
}

int	ok_chars(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_keylen(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}
