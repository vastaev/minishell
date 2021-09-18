#include "mini.h"

void	ft_exchild(t_cmdito *tmp, int fd[2], int old_fd[2])
{
	int	check;

	if (tmp->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (old_fd[1] != -1)
	{
		close(old_fd[1]);
		dup2(old_fd[0], STDIN_FILENO);
		close(old_fd[0]);
	}
	check = ft_redir(tmp->io, 1);
	if (ft_isbuiltin(tmp->args) == 1 && check)
		ft_what_in_line(tmp->args, 1, tmp);
	else
	{
		signal(SIGINT, sig_fork);
		signal(SIGQUIT, sig_fork);
		execve(tmp->args[0], tmp->args, ft_list2array(g_sh.listEnv));
	}
}

void	ft_exparent(int fd[2], int old_fd[2], int i, int islast)
{
	signal(SIGINT, sig_fork);
	signal(SIGQUIT, sig_fork);
	if (i > 0)
		close(old_fd[0]);
	old_fd[0] = fd[0];
	old_fd[1] = fd[1];
	close(fd[1]);
	if (islast)
		close(fd[0]);
}

void	ft_cmds(t_cmdito *tmp, int old_fd[2], int *i, int islast)
{
	int		fd[2];

	if (ft_isbuiltin(tmp->args) && !g_sh.hasp)
	{
		if (ft_redir(tmp->io, 0))
			ft_what_in_line(tmp->args, 0, tmp);
	}
	else
	{
		if (pipe(fd) == -1)
			ft_error(127, "Pipe error\n", 0);
		if (!strncmp(tmp->args[0], "exit", 4) && g_sh.hasp)
		{
			ft_exparent(fd, old_fd, *i, islast);
			return ;
		}
		tmp->pid = fork();
		if (tmp->pid < 0)
			ft_error(errno, strerror(errno), 0);
		else if (tmp->pid == 0)
			ft_exchild(tmp, fd, old_fd);
		else
			ft_exparent(fd, old_fd, *i, islast);
		(*i)++;
	}
}

static void	get_errno(int i)
{
	int		ex;
	int		status;

	while (i-- > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			ex = WEXITSTATUS(status);
			errno = ex;
		}
	}
}

void	ft_exec(t_cmdito *cmd)
{
	int			i;
	int			islast;
	int			old_fd[2];
	t_cmdito	*tmp;

	i = 0;
	tmp = cmd;
	old_fd[0] = STDIN_FILENO;
	old_fd[1] = -1;
	while (tmp)
	{
		islast = 0;
		if (!tmp->next)
			islast = 1;
		if (tmp->args)
		{
			init_fds();
			if (!ft_isbuiltin(tmp->args))
				tmp->args[0] = ft_findbin(tmp->args);
			if (tmp->args[0])
				ft_cmds(tmp, old_fd, &i, islast);
		}
		tmp = tmp->next;
	}
	get_errno(i);
}