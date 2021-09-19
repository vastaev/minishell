#include "mini.h"

int	ft_write_error_export(char *arg)
{
	write(2, "export: '", 10);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	check_for_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
		return (ft_write_error_export(arg));
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
			return (ft_write_error_export(arg));
		i++;
	}
	return (0);
}

void	ft_export(t_cmdito  *cmnd)
{
	t_env 	*ptr;
	int		i;

	sort_list();
	ptr = g_sh.listEnv;
	if (cmnd->n_ar == 1)
		while (ptr)
		{
			if (ptr->value)
				printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
			else
				printf("declare -x %s\n", ptr->name);
			ptr = ptr->next;
		}
	else
	{
		i = 1;
		while (i < cmnd->n_ar)
		{
			if (check_for_export(cmnd->args[i]) == 0)
			{
				if (ft_strchr(cmnd->args[i], '=') == 0)
					add_elem(&g_sh.listEnv, 
					new_env_elem(get_key(cmnd->args[i]), NULL));
				else
				{
					add_elem(&g_sh.listEnv, new_env_elem(get_key(cmnd->args[i]),
					get_value(cmnd->args[i])));
					ft_2d_array_free(g_sh.msEnvp);
					g_sh.msEnvp = ft_list2array(g_sh.listEnv);
				}
			}
			i++;
		}
	}
}