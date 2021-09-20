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

void	update_env_value_field(char *arg)
{
	t_env	*ptr;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] != '=')
		return ;
	ptr = g_sh.listEnv;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, arg, i) == 0)
		{
			if (ptr->value)
				free(ptr->value);
			ptr->value = get_value(arg);
			ft_2d_array_free(g_sh.msEnvp);
			g_sh.msEnvp = ft_list2array(g_sh.listEnv);	
			return ;
		}
		ptr = ptr->next;
	}
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
			// 	//если аргумент без равно и он существует, то ничего не происходит
			// 	//если аргумент с равно, то значение переписывается
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
}