#include "mini.h"

char	*get_value_ptr(char *toFind)
{
	t_env	*ptr;
	char	*pwd;

	ptr = g_sh.listEnv;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, toFind) == 0)
			break;
		ptr = ptr->next;
	}
	return (ptr->value);
}
