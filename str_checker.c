/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:29:07 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 15:36:31 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (-1);
}

static int	pipe_checker(t_args *args)
{
	t_args	*temp;

	temp = args;
	if (temp->pipe == 1)
		return (pipe_error());
	while (temp->next != NULL)
	{
		if (temp->pipe == 1 && temp->next->pipe == 1)
			return (pipe_error());
		temp = temp->next;
	}
	if (temp->pipe == 1)
		return (pipe_error());
	return (0);
}

static int	redir_next_to_redir(t_args *args)
{
	t_args	*temp;

	temp = args;
	if (args->redir > 0 && args_len(args) < 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd("newline'\n", 2);
		return (-1);
	}
	while (temp != NULL && temp->next != NULL)
	{
		if (temp->redir > 0 && temp->next->redir > 0)
			return (redir_error(temp->next));
		if (temp->redir > 0 && temp->next->pipe > 0)
			return (redir_error(temp->next));
		temp = temp->next;
	}
	return (0);
}

static int	redir_checker(t_args *args)
{
	t_args	*temp;

	temp = args;
	if (redir_next_to_redir(args) == -1)
		return (-1);
	while (temp->next != NULL)
		temp = temp->next;
	if (temp->redir != 0)
		return (redir_error(temp));
	return (0);
}

int	check_arg_errors(t_args *args)
{
	if (args == NULL)
		return (0);
	if (pipe_checker(args) == -1)
		return (-1);
	if (redir_checker(args) == -1)
		return (-1);
	if (args != NULL)
		return (1);
	return (0);
}
