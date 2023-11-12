/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:02:09 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 12:39:57 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_parser_check(t_args *temp)
{
	if (temp->next != NULL)
		return (1);
	else
		return (0);
}

void	str_redir_check(t_data *data, t_token *new, t_args *temp, int *cmds)
{
	if (temp->str != NULL && temp->redir != L_TWO && data->error != 1)
		(*cmds) += get_token_args(data, temp, new, *cmds);
}

static int	first_redir(t_data *data, t_token *new)
{
	int	y;

	y = 0;
	new->file = malloc(sizeof(int) * (data->args_len + 1));
	if (!new->file)
		return (FAIL);
	while (y < data->args_len)
		new->file[y++] = 0;
	new->redir_to = malloc(sizeof(char *) * (data->args_len + 1));
	if (!new->redir_to)
		return (FAIL);
	y = 0;
	while (y <= data->args_len)
		new->redir_to[y++] = NULL;
	return (SUCCESS);
}

static int	outfile_or_append(t_token *new, t_args *temp, int i)
{
	if (temp->redir == R_ONE)
	{
		new->redir_to[i] = ft_strdup(temp->next->str);
		if (!new->redir_to[i])
			return (FAIL);
		new->file[i] = OUTFILE;
		new->outfiles++;
	}
	else if (temp->redir == R_TWO)
	{
		new->redir_to[i] = ft_strdup(temp->next->str);
		if (!new->redir_to[i])
			return (FAIL);
		new->file[i] = APPEND;
		new->outfiles++;
	}
	return (SUCCESS);
}

int	has_redir(t_data *data, t_token *new, t_args *temp, int i)
{
	if (i == 0)
	{
		if (first_redir(data, new) == FAIL)
			return (FAIL);
	}
	if (temp->redir == L_ONE)
	{
		new->redir_to[i] = ft_strdup(temp->next->str);
		if (!new->redir_to[i])
			return (FAIL);
		new->file[i] = INFILE;
		new->infiles++;
	}
	else if (temp->redir == L_TWO)
	{
		data->heredoc_sign = 1;
		new->file[i] = INFILE;
		get_heredoc(data, new, temp, i);
	}
	else if (temp->redir == R_ONE || temp->redir == R_TWO)
	{
		if (outfile_or_append(new, temp, i) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}
