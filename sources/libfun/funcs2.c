#include "mini.h"

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	step;

	step = 0;
	while (src[step] != '\0')
	{
		dst[step] = src[step];
		step++;
	}
	dst[step] = '\0';
	return (strlen(src));
}

long long	ft_atoi(const char *str)
{
	int			shag;
	long long	res;
	int			minus;

	minus = 0;
	res = 0;
	shag = 0;
	while (str[shag] == ' ')
		shag++;
	if (str[shag] == '-')
		minus = 1;
	if ((str[shag] == '-') || (str[shag] == '+'))
		shag++;
	while (ft_isdigit(str[shag]))
	{
		res = res * 10 + (str[shag] - '0');
		shag++;
	}
	if (minus == 1)
		return (-res);
	else
		return (res);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sourc;

	dest = (unsigned char *)dst;
	sourc = (unsigned char *)src;
	if (dest == 0 && sourc == 0)
		return (0);
	while (n--)
		*dest++ = *sourc++;
	return (dst);
}

char	*ft_strdupchr(const char *s1, unsigned char c)
{
	char	*scopy;
	int		i;

	i = 0;
	while (s1[i] != c && s1[i])
		i++;
	scopy = malloc(i + 1);
	if (scopy == NULL)
		return (NULL);
	if (c == '\0')
		ft_memcpy(scopy, s1, i + 1);
	else
	{
		ft_memcpy(scopy, s1, i);
		scopy[i] = '\0';
	}
	return (scopy);
}

void	ft_2d_array_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}
