/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:01:24 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/28 19:07:54 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_startpoint(char *s1, char *set)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (set[x] != '\0')
	{
		while (s1[y] == set[x])
		{
			y++;
			x = 0;
		}
		x++;
	}
	return (y);
}

static int	ft_endpoint(char *s1, char *set, int strlen)
{
	int	x;

	x = 0;
	strlen = strlen - 1;
	while (set[x] != '\0')
	{
		while (s1[strlen] == set[x])
		{
			strlen--;
			x = 0;
		}
		x++;
	}
	return (strlen);
}

static int	ft_newlenght(int startpoint, int endpoint)
{
	int	newlen;

	newlen = 0;
	while (startpoint <= endpoint)
	{
		startpoint++;
		newlen++;
	}
	return (newlen);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		strlen;
	int		start;
	int		end;
	int		i;
	char	*newstr;

	i = 0;
	strlen = 0;
	if (!s1)
		return (NULL);
	strlen = ft_strlen(s1);
	start = ft_startpoint((char *)s1, (char *)set);
	end = ft_endpoint((char *)s1, (char *)set, strlen);
	strlen = ft_newlenght(start, end);
	newstr = (char *)malloc(sizeof(char) * strlen + 1);
	if (!newstr)
		return (NULL);
	while (i < strlen)
	{
		newstr[i] = s1[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
