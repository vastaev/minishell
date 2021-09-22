#include "mini.h"

int	change_dir(char *dir, char *oldpwd)
{
	char *newPwd;

	if (chdir(dir) == -1)
		return (1);
	newPwd = ft_strjoin("PWD=", dir);
	update_env_value_field(newPwd);
	return (0);
}

int	ft_cd(t_cmdito *cmnd)
{
	char	*tmp;

	if (cmnd->n_ar == 1)
	{
		if (find_env_key("HOME") != 1)
		{
			ft_errormsg("msh: cd: HOME not set\n");
			return (1);
		}
		change_dir(get_value_ptr("HOME"), NULL);
	}
	return (0);
}