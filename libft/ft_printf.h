/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:31:12 by tfinni            #+#    #+#             */
/*   Updated: 2023/03/06 01:20:31 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
char	*ft_uitoa(unsigned int n);
int		ft_argp(unsigned long p, char c, int start);
int		ft_argu(unsigned int nb);
int		ft_argx(unsigned int nb, char c, int start);
int		write_value_check(int value, int sign);
void	ft_putstr_fd_ftpf(char *s, int fd);
void	ft_putchar_fd_ftpf(char c, int fd);

#endif
