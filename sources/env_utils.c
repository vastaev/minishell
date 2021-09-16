#include "mini.h"

char    *ft_getenv(char *name)
{
    t_env   *ale;

    ale = g_sh.listEnv;
    while (ale)
    {
        if (!strncmp(name, ale->name, ft_strlen(ale->name) + 1))
            return (ale->value);
        ale = ale->next;
    }
    return (0);
}
