/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:15:46 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:15:47 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_fileexists(char *file)
{
	int			fd;
	struct stat	st;

	fd = open(file, O_RDONLY);
	if (fd > 0)
	{
		fstat(fd, &st);
		if (S_ISDIR(st.st_mode))
			return (0);
		close(fd);
		return (1);
	}
	return (0);
}

static void	free_bin(char **ar, char *f1, char *f2, char **ar2)
{
	int		i;

	i = -1;
	if (ar)
		ft_freetab(ar);
	if (f1)
		free(f1);
	if (f2)
		free(f2);
	if (ar2)
		while (ar2[++i])
			free(ar2[i]);
}

static char	**path_exists(void)
{
	char	**searchfolder;

	searchfolder = 0;
	if (!ft_getenv("PATH"))
		ft_error(127, "Error: path not found", 0);
	else
		searchfolder = ft_split(ft_getenv("PATH"), ':');
	return (searchfolder);
}

char	*ft_findbin(char **args)
{
	char	**searchfolder;
	char	*searchfile[2];
	int		i;

	i = -1;
	if (ft_fileexists(args[0]))
		return (args[0]);
	searchfolder = path_exists();
	if (!searchfolder)
		return (0);
	while (searchfolder[++i])
	{
		searchfile[0] = ft_strjoin(searchfolder[i], "/");
		searchfile[1] = ft_strjoin(searchfile[0], args[0]);
		if (ft_fileexists(searchfile[1]))
		{
			free_bin(searchfolder, searchfile[0], args[0], 0);
			errno = 0;
			return (searchfile[1]);
		}
		free_bin(0, searchfile[0], searchfile[1], 0);
	}
	free_bin(searchfolder, 0, 0, args);
	ft_error(127, "Command not found", 0);
	return (0);
}