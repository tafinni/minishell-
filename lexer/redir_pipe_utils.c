/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:43:53 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/08 13:44:30 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_not_first(t_data *data, int *len, int i)
{
	data->prev_redir = 1;
	(*len)--;
	return (i);
}

int	redir_first(t_data *data, t_args *node, int *len, int i)
{
	i = count_redir(node, data->input, len, i);
	data->prev_redir = 2;
	return (i);
}

int	pipe_first_or_not(t_data *data, t_args *node, int i, int flag)
{
	if (flag == 1)
	{
		node->pipe = 1;
		data->prev_pipe = 2;
	}
	else if (flag == 2)
		data->prev_pipe = 1;
	return (i);
}
