/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:15:23 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:15:25 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	check_sec(t_token *tmp)
{
	while (tmp->next)
	{
		if (tmp->tkn == tmp->next->tkn && tmp->tkn != 1
			&& printf("%s%s`%c'\n", RED, SYN_ERR, tmp->tkn))
			return (0);
		tmp = tmp->next;
	}
	if (tmp->tkn != 1 && tmp->tkn != 0 && tmp->tkn != ';'
		&& tmp->tkn != '&' && printf("%s%s`newline'\n", RED, SYN_ERR))
		return (0);
	if (!ft_strncmp(tmp->data, "", 2))
		return (0);
	return (1);
}

int	check_syn(const t_lexer *lex)
{
	t_token	*tmp;

	if (lex->esc == 1 && printf("%s%s`newline'\n", RED, SYN_ERR))
		return (0);
	if ((lex->state == 1 || lex->state == 0)
		&& printf("%s%s\n", RED, QUOTE_ERR))
		return (0);
	if ((lex->cb == 1)
		&& printf("%s%s\n", RED, CURLY_ERR))
		return (0);
	tmp = lex->tok;
	if (!ft_strncmp(tmp->data, ";", 2)
		&& printf("%s%s`%c'\n", RED, SYN_ERR, ';'))
		return (0);
	if ((tmp->tkn == '|' || tmp->tkn == '&' || tmp->tkn == ';')
		&& printf("%s%s`%c'\n", RED, SYN_ERR, tmp->tkn))
		return (0);
	if (!check_sec(tmp))
		return (0);
	return (1);
}

void	ft_errormsg(char *errormsg)
{
	write(2, errormsg, ft_strlen(errormsg));
}
