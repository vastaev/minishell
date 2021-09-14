#include "../includes/mini.h"

void	ft_echo(char **tabs)
{
	bool	flag;
	int		i;

	i = 1;
	flag = true;
	if (tabs[1])
	{
		if (ft_strcmp(tabs[1], "-n") == 0)
		{
			flag = false;
			i++;
		}
		while (tabs[i] != NULL)
		{
			ft_putstr_fd(tabs[i], 1);
			if (tabs[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (flag)
		write(1, "\n", 1);
}
