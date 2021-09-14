#include "../includes/mini.h"

int	ft_pwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * 4096);
	if (path == NULL)
		return (1);
	if (getcwd(path, 4096))
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
