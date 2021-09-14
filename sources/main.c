#include "../includes/mini.h"
t_shell	g_sh;

static void	signals(void)
{
	signal(SIGINT, sig_main);
	signal(SIGQUIT, SIG_IGN);
}

int	ft_what_in_line(char **tabs)
{
	if (ft_strcmp(tabs[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tabs[0], "echo") == 0)
		ft_echo(tabs);
	else if (ft_strcmp(tabs[0], "env") == 0)
		ft_env();
	return (0);
}

int main(int arg, char **argv, char **envp)
{
    char 	*line;
    char 	**tabs;
    int		i;

	init_shell(envp);
    while (21)
    {
        signals();
        line = ft_get_line();
        if (!line)
            continue ;
        tabs = ft_split(line, ' ');
		ft_what_in_line(tabs);
        i = -1;
        while (tabs[++i])
        {
            errno = 0;
            init_fds();
        }
    }
    return (0);
}