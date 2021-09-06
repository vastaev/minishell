#include "../includes/mini.h"

int main(int arg, char **argv, char **envp)
{
    char *line;
    char **tabs;
    int i;

    while (21)
    {
        line = ft_get_line();
        if (!line)
            continue ;
        tabs = ft_split(line, ';');
        i = -1;
        while (tabs[++i])
        {
            errno = 0;
        }
    }
    return (0);
}