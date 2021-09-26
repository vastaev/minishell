#include "mini.h"

char	*get_value_ptr(char *toFind)
{
	t_env	*ptr;

	ptr = g_sh.listEnv;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, toFind) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

int	set_new(char *oldOrPresent)
{
	char	tmp[2048];
	char	*pwd;
	char	*newPwd;
	t_env	*ptr;

	pwd = getcwd(tmp, 2048);
	if (!pwd)
		return (ft_print_errno());
	newPwd = ft_strjoin(oldOrPresent, pwd);
	ptr = find_env_key(newPwd);
	update_env_value_field(newPwd, ptr);
	free(newPwd);
	return (0);
}
