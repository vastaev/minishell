/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:20:40 by nephilister       #+#    #+#             */
/*   Updated: 2021/09/28 01:41:32 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
	return (1);
}

int	ft_write_error_arg(char *cmnd, char *arg)
{
	write(2, RED, 10);
	write(2, "msh: '", 5);
	write(2, cmnd, ft_strlen(cmnd));
	write(2, ": `", 3);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	errno = 1;
	return (1);
}
