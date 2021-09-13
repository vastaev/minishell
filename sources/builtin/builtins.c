#include "../includes/mini.h"

int	ft_pwd(void)
{
	char path[1024];

	if (getcwd(path, sizeof(path)))
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
	else
	{
		ft_print_errno();
		free(path);
		return(1);
	}
}

// void	ft_cd()
// {

// }