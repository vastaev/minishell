#include "mini.h"

static int	check_sec(t_token *tmp)
{
	while (tmp->next)
	{
		if (tmp->tkn == tmp->next->tkn && tmp->tkn != 1
			&& printf("%s`%c'\n", SYN_ERR, tmp->tkn))
			return (0);
		tmp = tmp->next;
	}
	if (tmp->tkn != 1 && tmp->tkn != 0 && tmp->tkn != ';'
		&& tmp->tkn != '&' && printf("%s`newline'\n", SYN_ERR))
		return (0);
	if (!ft_strncmp(tmp->data, "", 2))
		return (0);
	return (1);
}

int	check_syn(const t_lexer *lex)
{
	t_token	*tmp;

	if (lex->esc == 1 && printf("%s`newline'\n", SYN_ERR))
		return (0);
	if ((lex->state == 1 || lex->state == 0)
		&& printf("%s\n", QUOTE_ERR))
		return (0);
	if ((lex->cb == 1)
		&& printf("%s\n", CURLY_ERR))
		return (0);
	tmp = lex->tok;
	if (!ft_strncmp(tmp->data, ";", 2) && printf("%s`%c'\n", SYN_ERR, ';'))
		return (0);
	if ((tmp->tkn == '|' || tmp->tkn == '&' || tmp->tkn == ';')
		&& printf("%s`%c'\n", SYN_ERR, tmp->tkn))
		return (0);
	if (!check_sec(tmp))
		return (0);
	return (1);
}

void	ft_errormsg(char *errormsg)
{
	write(1, errormsg, ft_strlen(errormsg));
}