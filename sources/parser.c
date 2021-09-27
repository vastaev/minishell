/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:17:43 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:17:44 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char **append_arg(char *str, char **ar, int *n)
{
    char    **args;
    int     i;

    i = 0;
    if (!ar)
        args = ft_calloc(2, sizeof(char *));
    else 
        args = ft_calloc(*n + 2, sizeof(char *));
    while (ar && ar[i])
    {
        args[i] = ar[i];
        i++;
    }
    args[i] = ft_strdup(str);
    args[i + 1] = 0;
    free(str);
    free(ar);
    (*n)++;
    return (args);
}

static void deal_redir(t_lexer *lex, t_cmdito **cmd)
{
    char *ale;

    if (lex->tok->tkn != -45)
    {
        ale = lex->tok->next->data;
        lex->tok->next->data = ft_strtrim(ale, "'\"");
        free(ale);
    }
    if (lex->tok->tkn == '>')
        add_redir(&(*cmd)->io, new_io(lex->tok->next->data, 0, 1));
    else if (lex->tok->tkn == -44)
        add_redir(&(*cmd)->io, new_io(lex->tok->next->data, 1, 1));
    else if (lex->tok->tkn == '<')
        add_redir(&(*cmd)->io, new_io(lex->tok->next->data, 0, 0));
    else if (lex->tok->tkn == -45)
        read_heredoc(cmd, lex->tok->next->data);
    if (lex->tok)
        free(lex->tok->data);
    if (lex->tok->next)
        lex->tok = lex->tok->next;
}

static void build_commands(t_lexer *lex)
{
    t_cmdito *cmd;

    cmd = init_cmd();
    while (lex->tok && lex->tok->tkn != '|'
    && lex->tok->tkn != ';')
    {
        if (lex->tok->tkn == 1)
            cmd->args = append_arg(lex->tok->data, cmd->args, &cmd->n_ar);
        else if (lex->tok->tkn == '>' || lex->tok->tkn == '<'
        || lex->tok->tkn == -44 || lex->tok->tkn == -45)
            deal_redir(lex, &cmd);
        lex->tok = lex->tok->next;
    }
    if (lex->tok && lex->tok->tkn == '|')
        g_sh.hasp = 1;
    add_cmd(&g_sh.cmd, cmd);
    g_sh.nproc++;
}

static void parse(t_lexer lex)
{
    while (lex.tok)
    {
        build_commands(&lex);
        if (lex.tok && lex.tok->data)
            free(lex.tok->data);
        if (lex.tok)
            lex.tok = lex.tok->next;
    }
}

int lex_pars(char *str)
{
    t_lexer *lex;

    g_sh.cmd = 0;
    g_sh.hasp = 0;
    g_sh.nproc = 0;
    if (!lexer(str, &lex) || !check_syn(lex))
    {
        ft_freelex(&lex->tok, 1);
        free(lex->s);
		free(lex);
        return (0);
    }
    parse(*lex);
    ft_freelex(&lex->tok, 0);
	free(lex->s);
	free(lex);
    return (1);
}