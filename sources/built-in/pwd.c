/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:56 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/27 09:29:38 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_pwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * 4096);
	if (path == NULL)
		ft_error(-1, "Malloc error", 1);
	if (getcwd(path, 4096))
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
	else
	{
		ft_print_errno();
		free(path);
		return (1);
	}
}
