#include "mini.h"

void	change_env_field(char *key, char *newValue)
{
	int	keyLen;
	int	i;

	keyLen = ft_strlen(key);
	i = 0;
	while (ft_strncmp(g_sh.msEnvp[i], key, keyLen) != 0)
		i++;
	g_sh.msEnvp[i] = newValue;
}