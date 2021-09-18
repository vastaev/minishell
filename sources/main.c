#include "mini.h"

t_shell	g_sh;

static void	signals(void)
{
	signal(SIGINT, sig_main);
	signal(SIGQUIT, SIG_IGN);
}

int	ft_what_in_line(char **tabs, int fork, t_cmdito *cmnd)
{
	if (ft_strcmp(tabs[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tabs[0], "echo") == 0)
		ft_echo(tabs);
	else if (ft_strcmp(tabs[0], "env") == 0)
		ft_env();
	else if (ft_strcmp(tabs[0], "export") == 0)
		ft_export(cmnd);
    else
		ft_error(127, "Command not found", 0);
    if (fork == 1)
        exit(0);
	return (0);
}

int main(int arg, char **argv, char **envp)
{
    char 	*line;
    char 	**tabs;
    int		i;

	(void) arg;
	(void) argv;
	init_shell(envp);
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
            errno = 0;
            ft_exec(g_sh.cmd);
            ft_freecmd(g_sh.cmd);
            init_fds();
        }
        ft_freemain(tabs, line);
    }
    return (0);
}