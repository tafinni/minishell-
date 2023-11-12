/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:27:26 by tfinni            #+#    #+#             */
/*   Updated: 2023/08/31 12:04:12 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcount(char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				break ;
		}
		i++;
	}
	return (count);
}

static char	*ft_arrdup(char *s, char c, int i, int x)
{
	char	*res;
	char	found;

	found = 'N';
	while (*s != '\0' && found == 'N')
	{
		if (*s != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			found = 'Y';
		}
		if (found == 'N')
			s++;
	}
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	while (*s != '\0' && *s != c)
	{
		res[x] = *s++;
		x++;
	}
	res[x] = '\0';
	return (res);
}

static int	ft_nextstart(char *s, char c, int y)
{
	while (s[y] != '\0')
	{
		while (s[y] == c)
			y++;
		if (s[y] != c)
		{
			while (s[y] != c && s[y] != '\0')
				y++;
		}
		if (s[y] == c || s[y] == '\0')
			break ;
	}
	return (y);
}

static char	**ft_freeres(char **res, int strcount)
{
	int	i;

	i = 0;
	while (strcount > 0)
	{
		free(res[i]);
		i++;
		strcount--;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (ft_strcount((char *)s, c) + 1));
	if (!res)
		return (NULL);
	res[ft_strcount((char *)s, c)] = NULL;
	while (i < ft_strcount((char *)s, c))
	{
		res[i] = ft_arrdup((char *)(s + start), c, 0, 0);
		if (!res[i])
		{
			ft_freeres(res, ft_strcount((char *)s, c));
			return (NULL);
		}
		start = ft_nextstart((char *)s, c, start);
		i++;
	}
	return (res);
}
