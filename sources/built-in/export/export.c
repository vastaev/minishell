/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:45 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/28 02:17:14 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	input_validation(char *cmnd, char *arg)
{
	int	i;

	if (arg[0] == '=' || ft_isdigit(arg[0]) || !ok_chars(arg[0]))
		return (ft_write_error_arg(cmnd, arg));
	i = 0;
	if (ft_strcmp(cmnd, "export") == 0)
	{
		while (arg[i] && arg[i] != '=')
		{
			if (!ok_chars(arg[i]) && !ft_isdigit(arg[i]))
				return (ft_write_error_arg(cmnd, arg));
			i++;
		}
	}
	else
	{
		while (arg[i])
		{
			if ((!ok_chars(arg[i]) && !ft_isdigit(arg[i])) || arg[i] == '=')
				return (ft_write_error_arg(cmnd, arg));
			i++;
		}
	}
	return (0);
}

void	add_env_field(char *arg)
{
	if (ft_strchr(arg, '=') == 0)
		add_elem(&g_sh.listenv,
			new_env_elem(get_key(arg), NULL));
	else
	{
		add_elem(&g_sh.listenv, new_env_elem(get_key(arg),
				get_value(arg)));
		ft_2d_array_free(g_sh.msenvp);
		g_sh.msenvp = ft_list2array(g_sh.listenv);
	}
}

void	update_env_value_field(char *arg, t_env *ptr)
{
	if (ptr->value)
		free(ptr->value);
	ptr->value = get_value(arg);
	ft_2d_array_free(g_sh.msenvp);
	g_sh.msenvp = ft_list2array(g_sh.listenv);
}

void	print_export(void)
{
	t_env	*ptr;

	ptr = g_sh.listenv;
	while (ptr)
	{
		if (ptr->value)
			printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
		else
			printf("declare -x %s\n", ptr->name);
		ptr = ptr->next;
	}
}

int	ft_export(t_cmdito *cmnd)
{
	int		i;
	t_env	*found_ptr;

	if (cmnd->n_ar == 1)
		print_export();
	else
	{
		i = 1;
		while (cmnd->args[i])
		{
			if (input_validation("export", cmnd->args[i]) == 0)
			{
				found_ptr = find_env_key(cmnd->args[i]);
				if (found_ptr == NULL)
					add_env_field(cmnd->args[i]);
				else
					update_env_value_field(cmnd->args[i], found_ptr);
			}
			i++;
		}
	}
	return (0);
}
