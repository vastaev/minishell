#include "mini.h"

static unsigned int	est1i(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	unsigned int	razmer;
	char			*na4alo;
	char			*konec;
	char			*rezult;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] && est1i(s1[i], set))
		i++;
	na4alo = (char *)&s1[i];
	i = (ft_strlen(s1) - 1);
	if (i != -1)
		while (i >= 0 && est1i(s1[i], set))
			i--;
	konec = (char *)&s1[i];
	if (!*s1 || konec == na4alo)
		razmer = 2;
	else
		razmer = konec - na4alo + 2;
	rezult = malloc(sizeof(char) * razmer);
	ft_strlcpy(rezult, na4alo, razmer);
	return (rezult);
}

void	*ft_calloc(size_t count, size_t size)
{
	char			*ale;
	unsigned int	summa;
	unsigned int	i;

	summa = count * size;
	ale = malloc(summa);
	i = 0;
	if (!ale)
		return (0);
	while (summa--)
		ale[i++] = 0;
	return ((void *)ale);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rezult;
	size_t	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	rezult = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	if (!rezult)
		return (0);
	while (*s1)
		rezult[i++] = *s1++;
	while (*s2)
		rezult[i++] = *s2++;
	rezult[i] = '\0';
	return (rezult);
}

char	*ft_strrchr(char *s, int c)
{
	int	len;

	len = ft_strlen((char *)s);
	while (len >= 0 && s[len] != (char)c)
		len--;
	if (s[len] == (char)c)
		return ((char *)&s[len]);
	return (0);
}