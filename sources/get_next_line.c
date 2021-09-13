#include "mini.h"

void	mem_cpy(char *src, char *src2, int a, int stop)
{
	while (*src && a--)
		*(src2++) = *(src++);
	*src2++ = 0;
	if (stop)
		while (*src2)
			*src2++ = 0;
}

int	reads(int fd, char **line, char *buff)
{
	int		len;
	int		reads;
	char	*buff2;

	buff2 = buff;
	while (21)
	{
		if (!*buff)
			reads = read(fd, buff, BUFFER_SIZE);
		while (*buff && *buff != '\n')
			buff++;
		len = buff - buff2;
		if (*buff == '\n' || reads == 0)
		{
			line = malloc(len + 1);
			if (!(*line))
				return (0);
			mem_cpy(buff2, *line, len, 0);
			mem_cpy(++buff, buff2, BUFFER_SIZE, 1);
			if (reads != 0)
				return (1);
			else
				return (0);
		}
	}
}

char *get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char *line;

	if (!line || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	line = 0;
	reads(fd, &line, buff);
	return (&line);
}