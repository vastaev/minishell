#include "mini.h"

int lex_pars(char *str)
{
    t_lex *lex;

    g_sh.cmd = 0;
    g_sh.hasp = 0;
    g_sh.nproc = 0;
    if (!lexer(str, &lex) || !check_syn(str))
    {
        free(lex);
        return (0);
    }
    parse(*lex);
    free(lex);
    return (1);
}