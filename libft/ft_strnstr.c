/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:15:21 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/28 16:32:32 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		y;
	char		*ptr;

	ptr = (char *)haystack;
	i = 0;
	y = 0;
	if (haystack && *needle == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	if (needle[0] == '\0' || needle == NULL || len == (size_t) NULL)
		return ((char *)haystack);
	while (ptr[i] != '\0' && i < len)
	{
		while (ptr[i + y] == needle[y] && i + y < len)
		{
			if (needle[y + 1] == '\0')
				return (&ptr[i]);
			y++;
		}
		y = 0;
		i++;
	}
	return (NULL);
}
