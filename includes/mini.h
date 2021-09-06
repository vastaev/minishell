#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <termios.h>
# include <term.h>
# include <signal.h>

// libfun -------------------------------------------------------------
int	            ft_strlcpy(char *dst, const char *src, size_t dstsize);
unsigned int	ft_strlen(char const *str);
char	        **ft_split(char const *s, char c);
char	        *ft_strjoin(char const *s1, char const *s2);
char	        *ft_strrchr(char *s, int c);
char	        *ft_strtrim(char const *s1, char const *set);
void	        *ft_calloc(size_t count, size_t size);
// --------------------------------------------------------------------
// shellfun -----------------------------------------------------------
char            *ft_get_line(void);
char            *ft_prompt(void);
// --------------------------------------------------------------------
#endif