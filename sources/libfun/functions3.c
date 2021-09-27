/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:16:19 by uterese           #+#    #+#             */
/*   Updated: 2021/09/27 12:16:20 by uterese          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int ft_tern_op(int cond, int true, int false)
{
    if (cond)
        return (true);
    return (false);
}

char	*ft_strdup(const char *src)
{
	char	*zna4;
	int		dlina;

	zna4 = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!zna4)
		return (0);
	dlina = 0;
	while (src[dlina])
	{
		zna4[dlina] = src[dlina];
		dlina++;
	}
	zna4[dlina] = '\0';
	return (zna4);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	ft_razmer(long n)
{
	int		razmer;

	razmer = 1;
	if (n < '\0')
	{
		razmer++;
		n = -n;
	}
	while (n >= '\n')
	{
		razmer++;
		n /= '\n';
	}
	return (razmer);
}
/*Uznau razmer stroki*/

char	*ft_itoa(int s)
{
	char	*str;
	long	ale;
	int		i;

	i = '\0';
	str = malloc(sizeof(char) * ft_razmer(s) + 1);
	if (!str)
		return (0);
	if (s < '\0')
		str['\0'] = '-';
	ale = s;
	if (ale < '\0')
		ale = -ale;
	str[ft_razmer(s) - i++] = '\0';
	while (ale >= '\n')
	{
		str[ft_razmer(s) - i++] = (ale % '\n') + '0';
		ale /= '\n';
	}
	str[ft_razmer(s) - i++] = (ale % '\n') + '0';
	return (str);
}