/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <and nephilister>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:16:02 by uterese           #+#    #+#             */
/*   Updated: 2021/09/28 01:27:09 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;

	if (!dst || !src)
		return (0);
	a = 0;
	while (src[a])
		a++;
	if (dstsize == 0)
		return (a);
	a = 0;
	while (src[a] && a < dstsize - 1)
	{
		dst[a] = src[a];
		a++;
	}
	dst[a] = 0;
	a = 0;
	while (src[a])
		a++;
	return (a);
}

unsigned int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	ft_nomer_stroki(char const *stroka, char c)
{
	unsigned int	i;
	unsigned int	nomer;

	if (!stroka[0])
		return (0);
	i = 0;
	nomer = 0;
	while (stroka[i] && stroka[i] == c)
		i++;
	while (stroka[i])
	{
		if (stroka[i] == c)
		{
			nomer++;
			while (stroka[i] && stroka[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (stroka[i - 1] != c)
		nomer++;
	return (nomer);
}

static void	ft_sled_stroka(char **sledstr, unsigned int *sleddlina,
	char c)
{
	unsigned int	i;

	*sledstr += *sleddlina;
	*sleddlina = 0;
	i = 0;
	while (**sledstr && **sledstr == c)
		(*sledstr)++;
	while ((*sledstr)[i])
	{
		if ((*sledstr)[i] == c)
			return ;
		(*sleddlina)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	unsigned int	nomer;
	char			**otvet;
	unsigned int	sleddlina;
	char			*sledstr;
	unsigned int	i;

	if (!s)
		return (0);
	nomer = ft_nomer_stroki(s, c);
	otvet = malloc(sizeof(char *) * (nomer + 1));
	i = 0;
	sledstr = (char *)s;
	sleddlina = 0;
	if (!otvet)
		return (0);
	while (i < nomer)
	{
		ft_sled_stroka(&sledstr, &sleddlina, c);
		otvet[i] = malloc(sizeof(char) * (sleddlina + 1));
		ft_strlcpy(otvet[i], sledstr, sleddlina + 1);
		i++;
	}
	otvet[i] = 0;
	return (otvet);
}
