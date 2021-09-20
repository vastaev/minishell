#include "mini.h"

void    ft_exit(int a)
{
    if (a == 0)
    {
        printf("%sExit\n", RED);
        exit(0);
    }
}