/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:20:08 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/18 19:30:25 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*src;
	char	*dup;
	int		i;
	int		x;

	src = (char *)s1;
	i = 0;
	x = 0;
	while (src[i] != '\0')
		i++;
	dup = malloc(sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	while (src[x] != '\0')
	{
		dup[x] = src[x];
		x++;
	}
	dup[x] = '\0';
	return (dup);
}
