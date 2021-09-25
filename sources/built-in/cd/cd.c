#include "mini.h"

int	msh_change_dir(char *dir)
{
	if (ft_strcmp(dir, get_value_ptr("OLDPWD")) != 0)
		if (set_new("OLDPWD=") == 1)
			return (1);
	if (chdir(dir) == -1)
		return (1);	
	if (set_new("PWD=") == 1)
		return(1);
	return (0);
}

int	cd_to(char *key)
{
	if (find_env_key(key) != 1)
		return (ft_write_cd_not_set(key));
	msh_change_dir(get_value_ptr(key));
	return (0);	
}

int	where_to_cd(t_cmdito *cmnd)
{
	if (ft_strcmp(cmnd->args[1], "-") == 0)
	{
		if (cd_to("OLDPWD") == 1)
			return (1);
	}
	else if (ft_strcmp(cmnd->args[1], "~") == 0)
		ft_cd(cmnd, 1);
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