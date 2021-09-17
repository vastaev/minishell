#include "mini.h"

void	ft_export()
{
	t_env *ptr;

	sort_list();
	ptr = g_sh.listEnv;
	while (ptr->next)
	{
		printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}

}