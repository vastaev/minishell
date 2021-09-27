#include "mini.h"

int	input_validation(char *cmnd, char *arg)
{
	int	i;

	if (arg[0] == '=' || ft_isdigit(arg[0]) || !ok_chars(arg[0]))
		return (ft_write_error_arg(cmnd, arg));
	i = 0;
	if (ft_strcmp(cmnd, "export") == 0)
		while (arg[i] && arg[i] != '=')
		{
			if (!ok_chars(arg[i]) && !ft_isdigit(arg[i]))
				return (ft_write_error_arg(cmnd, arg));
			i++;
		}
	else
		while (arg[i])
		{
			if ((!ok_chars(arg[i]) && !ft_isdigit(arg[i])) || arg[i] == '=')
				return (ft_write_error_arg(cmnd, arg));
			i++;
		}	
	return (0);
}

void	add_env_field(char *arg)
{
	if (ft_strchr(arg, '=') == 0)
		add_elem(&g_sh.listEnv,
		new_env_elem(get_key(arg), NULL));
	else
	{
		add_elem(&g_sh.listEnv, new_env_elem(get_key(arg),
		get_value(arg)));
		ft_2d_array_free(g_sh.msEnvp);
		g_sh.msEnvp = ft_list2array(g_sh.listEnv);
	}
}

void	update_env_value_field(char *arg, t_env *ptr)
{
	if (ptr->value)
		free(ptr->value);
	ptr->value = get_value(arg);
}

void	print_export(void)
{
	t_env 	*ptr;

	ptr = g_sh.listEnv;
	while (ptr)
	{
		if (ptr->value)
			printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
		else
			printf("declare -x %s\n", ptr->name);
		ptr = ptr->next;
	}
}

int	ft_export(t_cmdito  *cmnd)
{
	int		i;
	t_env	*foundPtr;

	if (cmnd->n_ar == 1)
		print_export();
	else
	{
		i = 1;
		while (cmnd->args[i])
		{
			if (input_validation("export", cmnd->args[i]) == 0)
			{
				foundPtr = find_env_key(cmnd->args[i]);
				if (foundPtr == NULL)
					add_env_field(cmnd->args[i]);
				else
					update_env_value_field(cmnd->args[i], foundPtr);
			}
			i++;
		}
	}
	return (0);
}