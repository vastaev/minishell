#include "mini.h"

void	ft_error(int errnum, char *errmsg, int bye)
{
	write(1, errmsg, ft_strlen(errmsg));
	errno = errnum;
	if (bye == 1)
		exit(errnum);
	write(1, "\n", 1);
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