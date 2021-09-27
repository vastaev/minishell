/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:15:04 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:15:06 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_freetab(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		if (tabs[i])
		{
			free(tabs[i]);
			tabs[i] = NULL;
		}
		i++;
	}
	free(tabs);
	tabs = NULL;
}

void	ft_freecmd(t_cmdito *cmd)
{
	t_cmdito	*tmp;

	while (cmd)
	{
		tmp = cmd;
		if (!cmd->freed && cmd->args)
			ft_freetab(cmd->args);
		if (cmd->io)
			ft_freeio(&cmd->io);
		cmd = cmd->next;
		free(tmp);
	}
	free(cmd);
}

void	ft_freelex(t_token **lst, int flag)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->data && flag == 1)
			free((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_freeio(t_io **lst)
{
	t_io	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->name);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_freemain(char **tabs, char *line)
{
	if (tabs)
		ft_freetab(tabs);
	free(line);
}
