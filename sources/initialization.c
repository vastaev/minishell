/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:40 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/27 09:24:00 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_key(char *s)
{
	char	*key;

	key = ft_strdupchr(s, '=');
	return (key);
}

char	*get_value(char *s)
{
	char	*value;
	int		i;

	i = ft_keylen(s);
	if (s[i] != '=')
		return (NULL);
	value = ft_strdup(s + i + 1);
	if (!value)
		ft_error(-1, "Malloc error", 1);
	return (value);
}

void	update_shlvl()
{
	t_env	*ptr;
	int		tmp;

	ptr = g_sh.listEnv;
	while (ptr)
	{
		if (ft_strcmp("SHLVL", ptr->name) == 0)
			break;
		ptr = ptr->next;
	}
	tmp = ft_atoi(ptr->value);
	free(ptr->value);
	ptr->value = ft_itoa(tmp + 1);
	ft_2d_array_free(g_sh.msEnvp);
	g_sh.msEnvp = ft_list2array(g_sh.listEnv);
}

void	init_shell(int arg, char *argv[], char *envp[])
{
	int	arrLen;
	int	i;

	(void) arg;
	(void) argv;
	dup2(STDIN_FILENO, g_sh.fd[0]);
    dup2(STDOUT_FILENO, g_sh.fd[1]);
	arrLen = ft_2d_array_len(envp);
	g_sh.msEnvp = malloc(sizeof(char *) * (arrLen + 1));
	if (!g_sh.msEnvp)
		ft_error(-1, "Malloc error", 1);
	i = 0;
	while (i < arrLen)
	{
		g_sh.msEnvp[i] = ft_strdup(envp[i]);
		add_elem(&g_sh.listEnv, 
		new_env_elem(get_key(g_sh.msEnvp[i]), get_value(g_sh.msEnvp[i])));
		i++;
	}
	g_sh.msEnvp[i] = NULL;
	update_shlvl();
	sort_list();
}
