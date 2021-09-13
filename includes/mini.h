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
# include <fcntl.h>

# define BUFFER_SIZE 1
# define SYN_ERR "Error: near unspeacted token"
# define QUOTE_ERR "Error: missing enclosing quotation mark"
# define CURLY_ERR "Error: missing enclosing curly brace"
# define GRN "\001\e[0;32m\002"
# define RED "\001\e[0;31m\002"
# define WHT "\001\e[0m\002"

typedef struct s_lex
{
    char	*s;
	t_token	*tok;
	int		esc;
	int		state;
	int		cb;
}   t_lexer;

typedef struct s_token
{
	char			*data;
	int				tkn;
	struct s_token	*next;
}	t_token;

typedef struct s_io
{
	char		*name;
	int			is_out;
	int			is_app;
	struct s_io	*next;
}	t_io;

typedef struct s_cmdito
{
	char			**args;
	int				n_ar;
	t_io			*io;
	pid_t			pid;
	int				freed;
	struct s_cmdito	*next;
}					t_cmdito;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_shell
{
    t_cmdito *cmd;
    int fd[2];
    int nproc;
    int hasp;
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
int             ft_tern_op(int cond, int true, int false);
char	        *ft_strdup(char *src);
int	            ft_strncmp(char *s1, char *s2, unsigned int n);
char	        *ft_itoa(int s);
int	            ft_isalpha(int c);
int	            ft_isdigit(int c);
int	            ft_isalnum(int c);
// --------------------------------------------------------------------
// shellfun -----------------------------------------------------------
char            *ft_get_line(void);
char            *ft_prompt(void);
void            sig_main(int sig);
void	        init_fds(void);
void	        ft_error(int errornum, char *errormsg, int bye);
// --------------------------------------------------------------------
// parserfun-----------------------------------------------------------
int             lex_pars(char *str);
// --------------------------------------------------------------------
#endif