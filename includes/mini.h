#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

// libfun
int	ft_strlcpy(char *dst, const char *src, size_t dstsize);
unsigned int	ft_strlen(char const *str);
char	**ft_split(char const *s, char c);

#endif