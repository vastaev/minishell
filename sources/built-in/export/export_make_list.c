/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_make_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:40 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/27 09:24:00 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*new_env_elem(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		ft_error(-1, "Malloc error", 1);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_elem(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}
