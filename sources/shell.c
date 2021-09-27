/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:18:12 by uterese           #+#    #+#             */
/*   Updated: 2021/09/28 01:34:18 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	set_state(char a, int *state)
{
	if (*state == 2 && a != ';')
	{
		if (a == '"')
			*state = 0;
		else if (a == '\'')
			*state = 1;
	}
	else if (a == '"' && *state == 0)
		*state = 2;
	else if (a == '\'' && *state == 1)
		*state = 2;
}

static char	*ft_reconstruct(char *line)
{
	int		state;
	int		i;
	char	*new;

	i = -1;
	state = 2;
	line = ft_strtrim(line, " \t");
	if (line[0] == ';' && printf("%s%s`%c'\n", RED, "Error: syntax ", ';'))
		return (0);
	new = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (line[++i])
	{
		new[i] = line[i];
		set_state(new[i], &state);
		if (new[i] == ';' && (state == 1 || state == 0
				|| (new[i - 1] == '\\')))
			new[i] = -44;
	}
	free(line);
	return (new);
}

char	*ft_prompt(void)
{
	char	*user;
	char	pdir[1024];
	char	*ale[3];
	char	*dir;

	user = getenv("USER");
	if (!user)
		user = "user";
	if (!getcwd(pdir, sizeof(pdir)))
		dir = "directory";
	else
		dir = pdir;
	if (!(errno == 0))
		ale[0] = ft_strjoin("\U0001F61F" GRN, user);
	else
		ale[0] = ft_strjoin("\U0001F642" GRN, user);
	ale[1] = ft_strjoin(" in \U0001F4C2" GRN, ++dir);
	ale[2] = ft_strjoin(ale[0], ale[1]);
	free(ale[0]);
	free(ale[1]);
	ale[0] = ft_strjoin(ale[2], " \u276f " WHT);
	free(ale[2]);
	return (ale[0]);
}

char	*ft_get_line(void)
{
	char	*ale;
	char	*line;
	char	*prompt;
	int		ale2;

	ale2 = errno;
	prompt = ft_prompt();
	ale = readline(prompt);
	if (!ale)
	{
		printf("%sExit\n", RED);
		exit(0);
	}
	errno = ale2;
	line = ft_reconstruct(ale);
	if (line && *line)
		add_history(line);
	free(ale);
	free(prompt);
	return (line);
}
