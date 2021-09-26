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

t_env	*find_env_key(char *arg)
{
	t_env	*ptr;
	char	*tmpKey;

	tmpKey = get_key(arg);
	if (!tmpKey)
		return (NULL);
	ptr = g_sh.listEnv;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, tmpKey) == 0)
		{
			free(tmpKey);
			return (ptr);
		}
		ptr = ptr->next;
	}
	free(tmpKey);
	return (NULL);
}

int	ok_chars(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	ft_keylen(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}
