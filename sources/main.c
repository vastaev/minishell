#include "mini.h"

t_shell	g_sh;

static void init_shell()
{
    dup2(STDIN_FILENO, g_sh.fd[0]);
    dup2(STDOUT_FILENO, g_sh.fd[1]);
}

static void	signals(void)
{
	signal(SIGINT, sig_main);
	signal(SIGQUIT, SIG_IGN);
}

int main()
{
    char *line;
    char **tabs;
    int i;

    init_shell();
    while (21)
    {
        signals();
        line = ft_get_line();
        if (!line)
            continue ;
        tabs = ft_split(line, ';');
        i = -1;
        while (tabs[++i])
        {
            if (!lex_pars(tabs[i]))
                continue ;
            printf("%s\n", g_sh.cmd->args[0]);
            printf("%d n_ar %d freed\n", g_sh.cmd->n_ar, g_sh.cmd->freed);
            errno = 0;
            ft_freecmd(g_sh.cmd);
            init_fds();
        }
        ft_freemain(tabs, line);
    }
    return (0);
}