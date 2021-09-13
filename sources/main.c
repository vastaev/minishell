#include "mini.h"

t_shell	g_sh;

static void init_shell(void)
{
    dup2(STDIN_FILENO, g_sh.fd[0]);
    dup2(STDOUT_FILENO, g_sh.fd[1]);
}

static void	signals(void)
{
	signal(SIGINT, sig_main);
	signal(SIGQUIT, SIG_IGN);
}

int main(int arg, char **argv, char **envp)
{
    char *line;
    char **tabs;
    int i;
    init_shell();
    while (21)
    {
        if (!lex_pars(tabs[i]))
            continue ;
        signals();
        line = ft_get_line();
        if (!line)
            continue ;
        tabs = ft_split(line, ';');
        i = -1;
        while (tabs[++i])
        {
            errno = 0;
            init_fds();
        }
        // ft_freemain(tabs, line);
    }
    return (0);
}