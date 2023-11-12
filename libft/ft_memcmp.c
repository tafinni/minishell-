/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:17:26 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/15 20:22:57 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	size_t			y;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	y = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n > i || n > y || (int)n > 0)
	{
		if (str1[i] != str2[y])
			return (str1[i] - str2[y]);
		i++;
		y++;
		n--;
	}
	return (0);
}
