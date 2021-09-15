#include "mini.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	int	ale;
	int	ale2;

	ale = ft_isalpha(c);
	ale2 = ft_isdigit(c);
	if (ale == 1 || ale2 == 1)
		return (1);
	return (0);
}

char	*ft_strchr(char *s, int c)
{
	while (*s != (char)c && *s)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t				i;
	char				*otvet;

	if (!s)
		return (0);
	otvet = malloc(sizeof(char) * 1);
	if (!otvet)
		return (0);
	if ((size_t)ft_strlen(s) <= len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
	{
		otvet[0] = '\0';
		return (otvet);
	}
	free(otvet);
	otvet = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		otvet[i] = s[start + i];
		i++;
	}
	otvet[i] = '\0';
	return (otvet);
}