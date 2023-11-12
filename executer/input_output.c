/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:28:41 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/11 18:24:58 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in_out(t_token *temp)
{
	if (temp->cmd_str == NULL)
		exit(g_ret_number);
	if (temp->in < 0 || temp->out < 0)
		exit(g_ret_number);
	dup2(temp->in, 0);
	close(temp->in);
	dup2(temp->out, 1);
	close(temp->out);
}

static int	set_in(t_token *temp, int *ins, int i)
{
	close(temp->in);
	temp->in = open(temp->redir_to[i], O_RDONLY);
	if (temp->in < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->redir_to[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_ret_number = 1;
		return (-1);
	}
	(*ins)++;
	if (*ins != temp->infiles)
		close(temp->in);
	return (0);
}

static int	set_out(t_token *temp, int *outs, int i)
{
	close (temp->out);
	if (temp->file[i] == APPEND)
		temp->out = open(temp->redir_to[i], O_WRONLY 
				| O_CREAT | O_APPEND, 0644);
	else if (temp->file[i] == OUTFILE)
		temp->out = open(temp->redir_to[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp->out < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->redir_to[i], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		temp->error = 1;
		g_ret_number = 1;
		return (FAIL);
	}
	(*outs)++;
	if (*outs != temp->outfiles)
		close(temp->out);
	return (0);
}

static int	get_fd(t_token *temp)
{
	int	i;
	int	ins;
	int	outs;

	i = 0;
	ins = 0;
	outs = 0;
	while (temp->redir_to && temp->redir_to[i])
	{
		if (temp->file[i] != INFILE)
		{
			if (set_out(temp, &outs, i))
				return (-2);
		}
		else
		{
			if (set_in(temp, &ins, i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	get_output_input(t_data *data, t_token *temp, int p, int *fd)
{
	int	res;

	if (data->tokens_len == 1)
	{
		temp->in = dup(0);
		temp->out = dup(1);
		res = get_fd(temp);
		return (res);
	}
	if (p != 0)
		temp->in = fd[0];
	if (p != data->tokens_len - 1 && pipe(fd) == -1)
		ft_putstr_fd("minishell: pipe error\n", 2);
	if (p == 0)
	{
		temp->in = dup(0);
		temp->out = fd[1];
	}
	else if (p != 0 && p != data->tokens_len - 1)
		temp->out = fd[1];
	else
		temp->out = dup(1);
	res = get_fd(temp);
	return (res);
}
