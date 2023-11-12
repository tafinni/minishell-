/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:51:55 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/28 19:00:14 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
