#include "mini.h"

void	ft_export(t_cmdito  *cmnd)
{
	t_env *ptr;

	sort_list();
	ptr = g_sh.listEnv;
	if (cmnd->n_ar == 1)
		while (ptr->next)
		{
			printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
			ptr = ptr->next;
		}
}