#include "mini.h"

void	ft_error(int errnum, char *errmsg, int bye)
{
	printf("%s%s\n", RED, errmsg);
	errno = errnum;
	if (bye == 1)
		exit(errnum);
}

void	init_fds(void)
{
	dup2(g_sh.fd[0], STDIN_FILENO);
	dup2(g_sh.fd[1], STDOUT_FILENO);
}

void    sig_main(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void	sig_fork(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("%sQuit: 3\n", RED);
}

int	ft_isbuiltin(char **args)
{
	if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "pwd", 3))
		return (1);
	else if (ft_strlen(args[0]) == 2 && !ft_strncmp(args[0], "cd", 2))
		return (1);
	else if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "echo", 4))
		return (1);
	else if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "env", 3))
		return (1);
	else if (ft_strlen(args[0]) == 6 && !ft_strncmp(args[0], "export", 6))
		return (1);
	else if (ft_strlen(args[0]) == 5 && !ft_strncmp(args[0], "unset", 5))
		return (1);
	else if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "exit", 4))
		return (1);
	else
		return (0);
}