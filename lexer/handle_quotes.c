/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:05:03 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 12:40:58 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_single_quote(t_args *node, char *input, int *len, int i)
{
	node->quote = 1;
	if (node->counter == 0)
		node->expand = 1;
	node->counter++;
	i = check_quote(input, i, len);
	return (i);
}

static int	check_double_quote(t_args *node, char *input, int *len, int i)
{
	node->quote = 2;
	node->counter++;
	i = check_quote(input, i, len);
	return (i);
}

int	check_redir_quote(t_data *data, t_args *node, int i, int *len)
{
	int	check;

	check = i;
	while (data->input[i] && check_space(data->input[i]) == 0)
	{
		(*len)++;
		if ((data->input[i] == '<' && node->quote == 0 && check == i) || \
		(data->input[i] == '>' && node->quote == 0 && check == i))
			return (redir_first(data, node, len, i));
		else if ((data->input[i] == '<' && node->quote == 0) || \
		(data->input[i] == '>' && node->quote == 0))
			return (redir_not_first(data, len, i));
		else if (data->input[i] == '|' && i == check)
			return (pipe_first_or_not(data, node, i, 1));
		else if (data->input[i] == '|' && i != check)
			return (pipe_first_or_not(data, node, i, 2));
		else if (data->input[i] == '\"')
			i = check_double_quote(node, data->input, len, i);
		else if (data->input[i] == '\'')
			i = check_single_quote(node, data->input, len, i);
		if (i == -1)
			return (-1);
		i++;
	}
	return (i);
}
