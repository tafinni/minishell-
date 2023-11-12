/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:45:28 by tfinni            #+#    #+#             */
/*   Updated: 2023/01/14 21:02:05 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_getstrjoin(char *s1, char *s2)
{
	int		i;
	int		x;
	char	*str;

	x = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[x] != '\0')
	{
		str[x] = s1[x];
		x++;
	}
	while (s2[i] != '\0')
		str[x++] = s2[i++];
	str[x] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	if (c > 127)
		c = c - 256;
	while (ptr[i] != c && ptr[i] != '\0')
		i++;
	if (c == '\0' && i > 0 && ptr[i] == '\0')
		return (&ptr[i]);
	if (ptr[i] != c)
		return ((char *) NULL);
	if (ptr[i] == c)
		return (&ptr[i]);
	return ((char *) NULL);
}
