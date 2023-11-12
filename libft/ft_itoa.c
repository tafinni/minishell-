/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:14:48 by tfinni            #+#    #+#             */
/*   Updated: 2023/03/20 14:59:51 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	intlen;

	if (n < -2147483647)
		return (11);
	intlen = 0;
	if (n < 0)
	{
		intlen++;
		n = n * -1;
	}
	while (n > 0)
	{
		intlen++;
		n = n / 10;
	}
	return (intlen);
}

static char	*ft_tochar(int len, char *s, int n)
{
	s[len] = '\0';
	len--;
	while (n > 0)
	{
		s[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (s);
}

static char	*ft_minint(char *s)
{
	char	*minint;
	int		i;

	minint = "-2147483648";
	i = 0;
	while (minint[i] != '\0')
	{
		s[i] = minint[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;

	if (n == 0)
	{
		s = (char *)malloc(sizeof(char) * 2);
		if (!s)
			return (NULL);
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	len = ft_intlen(n);
	s = (char *)malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	if (n < -2147483647)
		return (ft_minint(s));
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	ft_tochar(len, s, n);
	return (s);
}
