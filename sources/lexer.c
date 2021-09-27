/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:16:57 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:16:58 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_token	*init_lexer(t_lexer **lex, char *s)
{
	t_token	*tok;

	(*lex) = malloc(sizeof(t_lexer));
	(*lex)->state = 2;
	(*lex)->esc = 0;
	(*lex)->cb = 0;
	(*lex)->tok = ft_calloc(1, sizeof(t_token));
	(*lex)->s = ft_strtrim(s, " ");
	tok = (*lex)->tok;
	tok->data = ft_calloc(1, sizeof(char));
	tok->tkn = 0;
	tok->next = 0;
	return (tok);
}

int	lexer(char *s, t_lexer **lex)
{
	int		i;
	t_token	*tok;

	i = 0;
	if (!s)
		return (0);
	tok = init_lexer(lex, s);
	while ((*lex)->s[i] != '\0')
	{
		if ((*lex)->state == 2)
			nrml_state(&i, &tok, lex);
		else if ((*lex)->state == 0)
			double_quotes(&i, &tok, lex);
		else if ((*lex)->state == 1)
			simple_quotes((*lex)->s[i], &tok, lex);
		i++;
	}
	return (1);
}
