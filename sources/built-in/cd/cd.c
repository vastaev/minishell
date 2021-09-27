#include "mini.h"

int	msh_change_dir(char *dir)
{
	t_env	*ptr;
	char	*tmp;

	if (chdir(dir) == -1)
		return (chdir_error(dir));
	tmp = ft_strjoin("OLDPWD=", get_value_ptr("PWD"));
	ptr = find_env_key("OLDPWD");
	update_env_value_field(tmp, ptr);
	free(tmp);
	if (set_new("PWD=") == 1)
		return(1);
	return (0);
}

int	cd_to(char *key)
{
	t_env	*ptr;

	ptr = find_env_key(key);
	if (ptr == NULL)
		return (ft_write_cd_not_set(key));
	msh_change_dir(ptr->value);
	return (0);	
}

int	where_to_cd(t_cmdito *cmnd)
{
	char	*tmp;

	if (ft_strcmp(cmnd->args[1], "-") == 0)
	{
		if (cd_to("OLDPWD") == 1)
			return (1);
		printf("%s\n", get_value_ptr("PWD"));
	}
	else if (cmnd->args[1][0] == '~')
	{
		tmp = ft_strjoin(getenv("HOME"), cmnd->args[1] + 1);
		msh_change_dir(tmp);
		free(tmp);
	}
	else
		msh_change_dir(cmnd->args[1]);
	return (0);
}

int	ft_cd(t_cmdito *cmnd, int flag)
{
	if (cmnd->n_ar == 1 || flag == 1)
	{
		cd_to("HOME");
		return (0);
	}
	else
		if (where_to_cd(cmnd) == 1)
			return (1);
	return (0);
}