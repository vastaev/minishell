/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_states.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:14:24 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:14:31 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	nrml_st_2(char *s, int *i, t_token **tok)
{
	const int	c_ty = get_type(s[*i]);

	if (c_ty == '|' || c_ty == ';' || c_ty == '>'
		|| c_ty == '<' || c_ty == '&')
	{
		new_token(tok);
		(*tok)->data = ft_strchjoin((*tok)->data, c_ty);
		if (s[*i + 1] && get_type(s[*i + 1]) == c_ty
			&& (c_ty == '>' || c_ty == '<'))
		{
			(*tok)->data = ft_strchjoin((*tok)->data, c_ty);
			(*tok)->tkn = ft_tern_op(c_ty == '>', -44, -45);
			(*i)++;
		}
		else
			(*tok)->tkn = c_ty;
		if (s[*i + 1] != '\0')
			new_token(tok);
	}
}

void	nrml_state(int *i, t_token **tok, t_lexer **lex)
{
	const int	c_ty = get_type((*lex)->s[*i]);

	if (c_ty == '\\')
		(*lex)->esc = 1;
	else if (((*lex)->esc && c_ty == -43) || c_ty == ';')
		deal_char(*tok, ';', (*lex)->state, lex);
	else if ((*lex)->cb && (*lex)->s[*i] == '}')
		(*lex)->cb = 0;
	else if ((*lex)->esc || c_ty == -42)
		deal_char(*tok, (*lex)->s[*i], (*lex)->state, lex);
	else if (c_ty == '"' || c_ty == '\'')
		(*lex)->state = ft_tern_op(c_ty == '"', 0, 1);
	else if (c_ty == ' ')
		new_token(tok);
	else if (c_ty == '$' && !(*lex)->esc)
		*i = expand_env(lex, *i, tok);
	else if (c_ty == '$')
		deal_char(*tok, (*lex)->s[*i], 2, lex);
	else
		nrml_st_2((*lex)->s, i, tok);
}

void	double_quotes(int *i, t_token **tok, t_lexer **lex)
{
	const int	c_ty = get_type((*lex)->s[*i]);

	if (c_ty == -43)
		(*tok)->data = ft_strchjoin((*tok)->data, ';');
	else if (c_ty == '$' && get_type((*lex)->s[*i - 1]) != '\\')
		*i = expand_env(lex, *i, tok);
	else if (c_ty != '\\' && c_ty != '"')
		(*tok)->data = ft_strchjoin((*tok)->data, (*lex)->s[*i]);
	if (c_ty == '"' && get_type((*lex)->s[*i - 1]) != '\\')
		(*lex)->state = 2;
	(*tok)->tkn = 1;
}

void	simple_quotes(char c, t_token **tok, t_lexer **lex)
{
	const int	c_ty = get_type(c);

	if (c_ty == -43)
		(*tok)->data = ft_strchjoin((*tok)->data, ';');
	else if (c_ty != '\'')
		(*tok)->data = ft_strchjoin((*tok)->data, c);
	if (c_ty == '\'')
		(*lex)->state = 2;
	(*tok)->tkn = 1;
}
