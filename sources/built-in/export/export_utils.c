#include "mini.h"
#include <string.h>

void	data_swap(t_env *ptr, t_env *ptr2, t_env *tmp)
{
	tmp->name = ptr->name;
	tmp->value = ptr->value;
	ptr->name = ptr2->name;
	ptr->value = ptr2->value;
	ptr2->name = tmp->name;
	ptr2->value = tmp->value;
}

void	sort_list()
{
	int	didSwap;
	t_env *ptr;
	t_env *tmp;

	tmp = malloc(sizeof(t_env));
	didSwap = 1;
	while (didSwap)
	{
		didSwap = 0;
		ptr = g_sh.listEnv;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				data_swap(ptr, ptr->next, tmp);
				didSwap = 1;
			}
			ptr = ptr->next;
		}
	}
	free(tmp);
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

int	ft_write_error_export(char *arg)
{
	write(2, "export: '", 10);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}
