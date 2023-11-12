/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:00:10 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/15 22:56:47 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	y;
	size_t	len;

	y = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (src[y] != '\0' && dstsize - 1 > y)
	{
		dst[y] = src[y];
		y++;
	}
	if (dstsize > y)
		dst[y] = '\0';
	return (len);
}
