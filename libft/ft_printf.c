/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:44:02 by tfinni            #+#    #+#             */
/*   Updated: 2023/03/06 01:24:07 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_args(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (write_value_check(write(1, "(null)", 6), 0) == -1)
			return (0);
		else
			return (6);
	}
	while (str[i])
		ft_putchar_fd_ftpf(str[i++], 1);
	return (i);
}

static int	ft_argid(int nb)
{
	char	*str;
	int		printlen;

	str = ft_itoa(nb);
	ft_putstr_fd_ftpf(str, 1);
	printlen = ft_strlen(str);
	free(str);
	return (printlen);
}

static int	ft_which(va_list args, const char c, int printlen)
{
	if (c == '%')
	{
		ft_putchar_fd_ftpf('%', 1);
		printlen++;
	}
	else if (c == 'c')
	{
		ft_putchar_fd_ftpf(va_arg(args, int), 1);
		printlen++;
	}
	else if (c == 's')
		printlen = ft_args(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		printlen = ft_argid(va_arg(args, int));
	else if (c == 'x' || c == 'X')
		printlen = ft_argx(va_arg(args, int), c, 0);
	else if (c == 'u')
		printlen = ft_argu(va_arg(args, unsigned int));
	else if (c == 'p')
		printlen = ft_argp(va_arg(args, unsigned long long), c, 0);
	if (printlen < 0)
		return (0);
	return (printlen);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		printlen;

	i = 0;
	printlen = 0;
	write_value_check(0, 1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			break ;
		if (str[i] == '%' && str[i++] != '\0')
			printlen = printlen + ft_which(args, str[i], 0);
		else
		{
			ft_putchar_fd_ftpf(str[i], 1);
			printlen++;
		}
		i++;
	}
	va_end(args);
	if (write_value_check(1, 0) < 0)
		return (-1);
	return (printlen);
}
