/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:45 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/27 09:27:26 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	msh_change_dir(t_env **env, char *dir, char *new)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, dir))
		{
			if (ptr->value)
				free(ptr->value);
			ptr->value = ft_strdup(new);
			free(new);
			return (1);
		}
		else
			ptr = ptr->next;
	}
	return (0);
}

static void	where_to_cd(char **args, char **old_dir, char **new_dir)
{
	char	*tmp;

	*old_dir = getcwd(0, 0);
	if (!args[1])
		*new_dir = ft_getenv("HOME");
	else if (args[1][0] == '-' && ft_getenv("OLDPWD"))
		*new_dir = ft_strdup(ft_getenv("OLDPWD"));
	else if (args[1][0] == '~')
	{
		tmp = ft_getenv("HOME");
		*new_dir = ft_strjoin(tmp, args[1] + 1);
	}
	else
		*new_dir = ft_strdup(args[1]);
}

int	ft_cd(char **args)
{
	char	*old_dir;
	char	*new_dir;
	int		error;

	where_to_cd(args, &old_dir, &new_dir);
	error = chdir(new_dir);
	if (new_dir)
		free(new_dir);
	new_dir = getcwd(0, 0);
	if (error == -1)
		ft_error(errno, strerror(errno), 0);
	else
	{
		msh_change_dir(&g_sh.listEnv, "OLDPWD", old_dir);
		msh_change_dir(&g_sh.listEnv, "PWD", new_dir);
	}
	return (0);
}
