/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:40 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/28 02:17:05 by uterese          ###   ########.fr       */
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

void	update_shlvl(void)
{
	t_env	*ptr;
	int		tmp;

	ptr = find_env_key("OLDPWD");
	if (ptr)
	{
		free(ptr->value);
		ptr->value = NULL;
	}
	else
		add_env_field("OLDPWD");
	ptr = g_sh.listenv;
	while (ptr)
	{
		if (ft_strcmp("SHLVL", ptr->name) == 0)
			break ;
		ptr = ptr->next;
	}
	tmp = ft_atoi(ptr->value);
	free(ptr->value);
	ptr->value = ft_itoa(tmp + 1);
	ft_2d_array_free(g_sh.msenvp);
	g_sh.msenvp = ft_list2array(g_sh.listenv);
}

void	init_shell(int arg, char *argv[], char *envp[])
{
	int	arrlen;
	int	i;

	(void) arg;
	(void) argv;
	if (*envp == 0)
		ft_error(127, "Error: envp not found!", 1);
	dup2(STDIN_FILENO, g_sh.fd[0]);
	dup2(STDOUT_FILENO, g_sh.fd[1]);
	arrlen = ft_2d_array_len(envp);
	g_sh.msenvp = malloc(sizeof(char *) * (arrlen + 1));
	if (!g_sh.msenvp)
		ft_error(-1, "Malloc error", 1);
	i = 0;
	while (i < arrlen)
	{
		g_sh.msenvp[i] = ft_strdup(envp[i]);
		add_elem(&g_sh.listenv,
			new_env_elem(get_key(g_sh.msenvp[i]), get_value(g_sh.msenvp[i])));
		i++;
	}
	g_sh.msenvp[i] = NULL;
	update_shlvl();
	sort_list();
}
