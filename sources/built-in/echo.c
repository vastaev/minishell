/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nephilister <nephilister@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:47 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/27 09:20:48 by nephilister      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"
#include "stdbool.h"

void	ft_echo(char **tabs)
{
	bool	flag;
	int		i;

	i = 1;
	flag = true;
	if (tabs[1])
	{
		if (ft_strcmp(tabs[1], "-n") == 0)
		{
			flag = false;
			i++;
		}
		while (tabs[i] != NULL)
		{
			ft_putstr_fd(tabs[i], 1);
			if (tabs[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (flag)
		write(1, "\n", 1);
}
