#include "../includes/mini.h"

static int	ft_charcmp(char c1, char c2)
{
	if (c1 == c2)
		return (1);
	else
		return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	step;

	step = 0;
	while (s1[step] && s2[step])
	{
		if (!ft_charcmp(s1[step], s2[step]))
			return ((unsigned char)s1[step] - (unsigned char)s2[step]);
		step++;
	}
	return ((unsigned char)s1[step] - (unsigned char)s2[step]);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

int	ft_2d_array_len(char **s)
{
	int	counter;

	counter = 0;
	while (s[counter] != NULL)
		counter++;
	return (counter);
}

size_t	ft_strcat(char *dst, const char *src)
{
	size_t	dlen;
	size_t	slen;
	size_t	offset;
	size_t	step;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	offset = dlen;
	step = 0;
	while (src[step] != '\0')
	{
		dst[offset] = src[step];
		step++;
		offset++;
	}
	dst[offset] = '\0';
	return (dlen + slen);
}
