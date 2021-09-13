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

# define GRN "\001\e[0;32m\002"
# define RED "\001\e[0;31m\002"
# define WHT "\001\e[0m\002"

typedef struct s_shell
{
    int fd[2];
}   t_shell;

extern t_shell  g_sh;

// libfun -------------------------------------------------------------
int	            ft_strlcpy(char *dst, const char *src, size_t dstsize);
unsigned int	ft_strlen(char const *str);
char	        **ft_split(char const *s, char c);
char	        *ft_strjoin(char const *s1, char const *s2);
char	        *ft_strrchr(char *s, int c);
char	        *ft_strtrim(char const *s1, char const *set);
void	        *ft_calloc(size_t count, size_t size);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putstr_fd(char *s, int fd);
// --------------------------------------------------------------------
// shellfun -----------------------------------------------------------
char            *ft_get_line(void);
char            *ft_prompt(void);
void            sig_main(int sig);
void	        init_fds(void);
void	        ft_error(int errornum, char *errormsg, int bye);
void			ft_print_errno(void);
// built-in -----------------------------------------------------------
int				ft_pwd(void);
// --------------------------------------------------------------------
#endif