/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:14:41 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:14:47 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini.h"

int	get_type(char c)
{
	const char	c_ty[12] = {'|', '\'', '"', ';', ' ',
		'>', '<', '&', '\\', '$', -44, '\0'};
	const char	e_ty[12] = {'|', '\'', '"',
			';', ' ', '>', '<', '&', '\\', '$', -43, 0};
	int						i;

	i = -1;
	while (c_ty[++i])
		if (c == c_ty[i])
			return (e_ty[i]);
	return (-42);
}

char	*ft_strchjoin(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new = malloc(sizeof(char) * i + 2);
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	return (new);
}

void	deal_char(t_token *tok, char c, int nstat, t_lexer **lex)
{
	tok->data = ft_strchjoin(tok->data, c);
	tok->tkn = 1;
	if ((*lex)->esc == 1)
		(*lex)->esc = 0;
	(*lex)->state = nstat;
}

void	new_token(t_token **tok)
{
	int	i;

	i = ft_strlen((*tok)->data);
	if (i > 0)
	{
		(*tok)->data[i] = '\0';
		(*tok)->next = ft_calloc(1, sizeof(t_token));
		(*tok) = (*tok)->next;
		(*tok)->tkn = 0;
		(*tok)->data = ft_calloc(1, sizeof(char));
	}
}