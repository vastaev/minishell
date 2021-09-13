#include "mini.h"

int ft_tern_op(int cond, int true, int false)
{
    if (cond)
        return (true);
    return (false);
}

char	*ft_strdup(char *src)
{
	char	*zna4enie;
	int		dlina;

	dlina = 0;
	while (src[dlina])
		dlina++;
	zna4enie = (char *)malloc(sizeof(char) * (dlina + 1));
	if (zna4enie == 0)
		return (0);
	zna4enie[dlina + 1] = '\0';
	while (dlina > 0)
	{
		zna4enie[dlina] = src[dlina];
		dlina--;
	}
	zna4enie[0] = src[0];
	return (&zna4enie[dlina]);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	ft_razmer(long n)
{
	int		razmer;

	razmer = 1;
	if (n < '\0')
	{
		razmer++;
		n = -n;
	}
	while (n >= '\n')
	{
		razmer++;
		n /= '\n';
	}
	return (razmer);
}
/*Uznau razmer stroki*/

char	*ft_itoa(int s)
{
	char	*str;
	long	ale;
	int		i;

	i = '\0';
	str = malloc(sizeof(char) * ft_razmer(s) + 1);
	if (!str)
		return (0);
	if (s < '\0')
		str['\0'] = '-';
	ale = s;
	if (ale < '\0')
		ale = -ale;
	str[ft_razmer(s) - i++] = '\0';
	while (ale >= '\n')
	{
		str[ft_razmer(s) - i++] = (ale % '\n') + '0';
		ale /= '\n';
	}
	str[ft_razmer(s) - i++] = (ale % '\n') + '0';
	return (str);
}