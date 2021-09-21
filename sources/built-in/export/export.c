#include "mini.h"

int	check_for_export(char *arg)
{
	int	i;

	if (arg[0] == '=' || ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
		return (ft_write_error_export(arg));
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
			return (ft_write_error_export(arg));
		i++;
	}
	return (0);
}

int	find_env_key(char *arg)
{
	int		i;
	t_env	*ptr;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	ptr = g_sh.listEnv;
	while (ptr != NULL)
	{
		if (ft_strncmp(ptr->name, arg, i) == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
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

	if (cmnd->n_ar == 1)
		print_export();
	else
	{
		i = 1;
		while (cmnd->args[i])
		{
			if (check_for_export(cmnd->args[i]) == 0)
			{
				if (find_env_key(cmnd->args[i]) == 0)
					add_env_field(cmnd->args[i]);
				else
					update_env_value_field(cmnd->args[i]);
			}
			i++;
		}
	}
	return (0);
}