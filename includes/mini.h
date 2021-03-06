/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:38:00 by uterese           #+#    #+#             */
/*   Updated: 2021/09/28 02:22:10 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define SYN_ERR "Error: near unexpected token"
# define QUOTE_ERR "Error: missing enclosing quotation mark"
# define CURLY_ERR "Error: missing enclosing curly brace"
# define GRN "\001\e[0;32m\002"
# define RED "\001\e[0;31m\002"
# define WHT "\001\e[0m\002"

typedef struct s_token
{
	char			*data;
	int				tkn;
	struct s_token	*next;
}	t_token;

typedef struct s_lex
{
	char	*s;
	t_token	*tok;
	int		esc;
	int		state;
	int		cb;
}	t_lexer;

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
}	t_cmdito;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char		**msenvp;
	t_env		*listenv;
	t_cmdito	*cmd;
	int			fd[2];
	int			nproc;
	int			hasp;
}	t_shell;

extern t_shell	g_sh;

// libfun -------------------------------------------------------------
int				ft_strlcpy(char *dst, const char *src, size_t dstsize);
unsigned int	ft_strlen(char const *str);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strrchr(char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
void			*ft_calloc(size_t count, size_t size);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_putstr_fd(char *s, int fd);
int				ft_2d_array_len(char **s);
int				ft_tern_op(int cond, int true, int false);
char			*ft_strdup(const char *src);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_itoa(int s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strchjoin(char *str, char c);
size_t			ft_strcat(char *dst, const char *src);
size_t			ft_strcpy(char *dst, const char *src);
long long		ft_atoi(const char *str);
char			*ft_strdupchr(const char *s1, unsigned char c);
void			ft_2d_array_free(char **s);
// --------------------------------------------------------------------
// shellfun -----------------------------------------------------------
int				get_next_line(int fd, char **line);
char			*ft_prompt(void);
void			sig_main(int sig);
void			init_fds(void);
char			*ft_getenv(char *name);
char			*ft_get_line(void);
void			sig_fork(int sig);
int				ft_what_in_line(char **tabs, int fork, t_cmdito *cmnd);
int				ft_isbuiltin(char **args);
char			**ft_list2array(t_env *env);
char			*ft_findbin(char **args);
int				ft_redir(t_io *io, int inb);
void			ft_exec(t_cmdito *cmd);
void			init_shell(int arg, char *argv[], char *envp[]);
// --------------------------------------------------------------------
// parserfun-----------------------------------------------------------
int				lex_pars(char *str);
t_cmdito		*init_cmd(void);
void			add_cmd(t_cmdito **lst, t_cmdito *add);
void			add_redir(t_io **lst, t_io *new);
void			read_heredoc(t_cmdito **cmd, char *del);
char			*get_val(char *str, int i, int ret);
int				get_len(char *str, int i);
t_io			*new_io(char *name, int is_app, int is_out);
// --------------------------------------------------------------------
// lexerfun------------------------------------------------------------
void			nrml_state(int *i, t_token **tok, t_lexer **lex);
void			double_quotes(int *i, t_token **tok, t_lexer **lex);
void			simple_quotes(char c, t_token **tok, t_lexer **lex);
int				lexer(char *s, t_lexer **lex);
int				get_type(char c);
void			deal_char(t_token *tok, char c, int nstat, t_lexer **lex);
void			new_token(t_token **tok);
int				expand_env(t_lexer **lex, int i, t_token **tok);
// --------------------------------------------------------------------
// errorsfun-----------------------------------------------------------
int				check_syn(const t_lexer *lex);
void			ft_errormsg(char *errormsg);
void			ft_error(int errornum, char *errormsg, int bye);
int				ft_print_errno(void);
int				ft_write_error_arg(char *cmnd, char *arg);
int				ft_write_cd_not_set(char *key);
int				chdir_error(char *dir);
// built-in -----------------------------------------------------------
int				ft_pwd(void);
void			ft_echo(char **tabs);
void			ft_env(void);
int				ft_export(t_cmdito *cmnd);
void			change_env_field(char *key, char *newValue);
void			add_elem(t_env **lst, t_env *new);
t_env			*new_env_elem(char *name, char *value);
void			sort_list(void);
char			*get_value(char *s);
char			*get_key(char *s);
void			ft_exit(int a);
void			add_env_field(char *arg);
void			update_env_value_field(char *arg, t_env *ptr);
int				ft_unset(t_cmdito *cmnd);
int				input_validation(char *cmnd, char *arg);
t_env			*find_env_key(char *arg);
int				ft_cd(char **args);
char			*get_value_ptr(char *toFind);
int				ok_chars(char c);
int				set_new(char *oldOrPresent);
int				ft_keylen(char *arg);
// --------------------------------------------------------------------
// freefun-------------------------------------------------------------
void			ft_freecmd(t_cmdito *cmd);
void			ft_freelex(t_token **lst, int flag);
void			ft_freeio(t_io **lst);
void			ft_freemain(char **tabs, char *line);
void			ft_freetab(char **tabs);
// --------------------------------------------------------------------
#endif
