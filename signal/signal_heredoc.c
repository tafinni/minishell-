/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:16:30 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/09 16:16:55 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		ft_printf("\033[1A");
		g_ret_number = -2;
	}
	else
	{
		g_ret_number = sig;
	}
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}
