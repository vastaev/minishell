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

int	ft_write_cd_not_set(char *key)
{
	write(2, RED, 10);
	write(2, "msh: cd: ", 10);
	write(2, key, ft_strlen(key));
	write(2, " not set\n", 10);
	errno = 1;
	return (1);
}

int	chdir_error(char *dir)
{
	write(2, RED, 10);
	ft_putstr_fd("msh: cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	ft_print_errno();
	errno = 1;
	return (1);
}
