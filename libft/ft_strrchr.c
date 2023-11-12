/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:24:09 by tfinni            #+#    #+#             */
/*   Updated: 2022/11/18 21:31:56 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	if (c > 128)
		c = c - 256;
	while (ptr[i] != '\0')
		i++;
	while (i > 0 && ptr[i] != c)
		i--;
	if (ptr[i] == c)
		return (&ptr[i]);
	else
		return ((char *) NULL);
}
