# include "mini.h"

char	*get_val(char *str, int i, int ret)
{
	char *line;
	char *ale;

	ale = ft_substr(str, i + 1, ret);
	line = ft_getenv(ale);
	if (!line)
		line = "";
	if (!ft_strncmp(ale, "_", 2))
	{
		free(ale);
		ale = line;
		line = ft_strrchr(line, '/');
		line++;
	}
	else if (str[i + 1] == '?')
		line = ft_itoa(errno);
	free(ale);
	return (line);
}

int get_len(char *str, int i)
{
	int count;

	count = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i] && str[i] != '_' ) && str[i] != '?')
			return (count);
		count++;
		i++;
	}
	return (count);
}

static void process_herestring(char *str, int fd, char *del)
{
	int i;
	int j;
	char *new;

	i = -1;
	if (ft_strchr(del, '"'))
		write(fd, str, ft_strlen(str));
	else
	{
		while(str[++i])
		{
			if (str[i] == '$')
			{
				j = get_len(str, i + 1);
				new = get_val(str, i, j);
				write(fd, new, ft_strlen(new));
				i += j;
			}
			else
				write(fd, &str[i], 1);
		}
	}
	write(fd, "\n", 1);
	free(str);
}

static char *get_file(void)
{
	char *file;
	char *ale[2];
	int i;
	struct stat buf;

	i = 0;
	while (++i)
	{
		ale[0] = ft_strdup("input");
		ale[1] = ft_itoa(i);
		file = ft_strjoin(ale[0], ale[1]);
		if (stat(file, &buf) == -1)
		{
			free(ale[0]);
			free(ale[1]);
			return (file);
		}
		free(file);
		free(ale[0]);
		free(ale[1]);
	}
	return (0);
}

void    read_heredoc(t_cmdito **cmd, char *del)
{
	char  *delim;
	char        *str;
	char        *file;
	int         fd;

	delim = del;
	file = get_file();
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (21)
	{
		write(1, "> ", 2);
		get_next_line(0, &str);
		if (!ft_strncmp(str, delim, ft_strlen(delim) + 1))
			break ;
		process_herestring(str, fd, delim);
	}
	free(str);
	free(del);
	close(fd);
	add_redir(&(*cmd)->io, new_io(file, 0, 0));
}