/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:55:37 by tfinni            #+#    #+#             */
/*   Updated: 2023/01/14 19:42:25 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_argu(unsigned int nb)
{
	char	*str;
	int		printlen;

	if (nb == 0)
	{
		ft_putchar_fd_ftpf('0', 1);
		return (1);
	}
	str = ft_uitoa(nb);
	ft_putstr_fd_ftpf(str, 1);
	printlen = ft_strlen(str);
	free(str);
	return (printlen);
}

int	ft_argx(unsigned int nb, char c, int start)
{
	static int	printlen;

	if (start++ == 0)
		printlen = 0;
	if (nb > 15)
	{
		ft_argx(nb / 16, c, 1);
		ft_argx(nb % 16, c, 1);
	}
	else
	{
		if (nb < 10)
			ft_putchar_fd_ftpf(nb + '0', 1);
		else
		{
			if (c == 'X')
				ft_putchar_fd_ftpf(nb - 10 + 'A', 1);
			if (c == 'x')
				ft_putchar_fd_ftpf(nb - 10 + 'a', 1);
		}
		printlen++;
	}
	return (printlen);
}

int	ft_argp(unsigned long p, char c, int start)
{
	static int	printlen;

	if (start++ == 0)
	{
		ft_putstr_fd_ftpf("0x", 1);
		printlen = 2;
	}
	if (p > 15)
	{
		ft_argp(p / 16, c, 1);
		ft_argp(p % 16, c, 1);
	}
	else
	{
		if (p < 10)
			ft_putchar_fd_ftpf(p + '0', 1);
		else
			ft_putchar_fd_ftpf(p - 10 + 'a', 1);
		printlen++;
	}
	return (printlen);
}
