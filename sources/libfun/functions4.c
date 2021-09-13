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
