/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_value_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:38:06 by tfinni            #+#    #+#             */
/*   Updated: 2023/03/06 01:19:17 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_value_check(int value, int sign)
{
	static int	res;

	if (sign == 1)
		res = 0;
	if (value < 0)
		res = -1;
	return (res);
}

void	ft_putchar_fd_ftpf(char c, int fd)
{
	write_value_check(write(fd, &c, 1), 0);
}

void	ft_putstr_fd_ftpf(char *s, int fd)
{
	if (!s)
		return ;
	while (*s != '\0')
	{
		ft_putchar_fd_ftpf(*s, fd);
		s++;
	}
}
