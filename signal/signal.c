/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:29:03 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/13 14:15:52 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(g_ret_number);
}

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_ret_number = 1;
	}
}

void	set_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sig_child(int signum)
{
	if (signum == SIGINT)
	{
		g_ret_number = 130;
		ft_putstr_fd("\n", 2);
	}
	else if (signum == SIGQUIT)
	{
		g_ret_number = 131;
		ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	set_signal_child(void)
{
	signal(SIGINT, handle_sig_child);
	signal(SIGQUIT, handle_sig_child);
}
