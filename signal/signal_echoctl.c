/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_echoctl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:37:34 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/08 13:38:59 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_echoctl(struct termios *t)
{
	t->c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, t);
}

void	reset_echoctl(struct termios *t)
{
	t->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, t);
}
