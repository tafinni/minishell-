/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:37:54 by tfinni            #+#    #+#             */
/*   Updated: 2023/01/14 18:20:58 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (str);
}
