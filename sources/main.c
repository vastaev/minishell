#include "../includes/mini.h"
t_shell	g_sh;

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
            errno = 0;
            init_fds();
        }
    }
    return (0);
}