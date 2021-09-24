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

int	set_new(char *oldOrPresent)
{
	char	tmp[2048];
	char	*pwd;
	char	*newPwd;

	pwd = getcwd(tmp, 2048);
	if (!pwd)
		return (ft_print_errno());
	newPwd = ft_strjoin(oldOrPresent, pwd);
	update_env_value_field(newPwd);
	free(newPwd);
	return (0);
}
