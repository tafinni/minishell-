/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:35:52 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/26 20:31:12 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;
	char	cc;

	i = 0;
	cc = (char)c;
	ptr = (char *)s;
	while (n > i && n > 0)
	{
		if (*ptr == cc)
			return (ptr);
		ptr++;
		i++;
	}
	return (NULL);
}
