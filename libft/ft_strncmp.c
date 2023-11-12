/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:51:42 by tfinni            #+#    #+#             */
/*   Updated: 2023/08/31 12:09:48 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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
		if (str1[i] != '\0')
			i++;
		if (str2[y] != '\0')
			y++;
		n--;
	}
	return (0);
}
