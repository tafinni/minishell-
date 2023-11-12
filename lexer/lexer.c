/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:39:31 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 15:54:04 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *input, int i, int *len)
{
	int		open_quote;
	int		counter;
	char	to_check;

	open_quote = 0;
	counter = 0;
	to_check = input[i];
	while (input[i])
	{
		counter++;
		i++;
		if (input[i] == to_check)
		{
			open_quote = 1;
			break ;
		}
	}
	if (open_quote == 0)
	{
		lexer_msg((to_check));
		return (-1);
	}
	*len += counter;
	return (i);
}

int	count_redir(t_args *node, char *input, int *len, int i)
{
	if (input[i] == '<' && input[i + 1] != '<')
		node->redir = L_ONE;
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		i++;
		node->redir = L_TWO;
	}
	else if (input[i] == '>' && input[i + 1] != '>')
		node->redir = R_ONE;
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		i++;
		node->redir = R_TWO;
	}
	(*len)--;
	return (i);
}

int	get_arg_node(t_data *data, t_args *node, char *input, int *i)
{
	int	len;

	len = 0;
	node->counter = 0;
	*i = check_redir_quote(data, node, *i, &len);
	if (*i == -1)
		return (FAIL);
	if (node->redir > 0)
		node->str = get_redir_str(node);
	else
	{
		node->str = ft_node_str(data, input, *i - len, len);
	}
	if (!node->str)
		return (FAIL);
	if (data->prev_pipe == 1)
		(*i)--;
	if (data->prev_redir == 1)
	{
		(*i)--;
		data->prev_pipe = 0;
		data->prev_redir = 0;
	}
	return (SUCCESS);
}

t_args	*str_to_arg_list(t_data *data, char *input, t_args *arg_list, int i)
{
	t_args	*node;

	while (input[i] && input)
	{
		node = NULL;
		if ((input[i] != 32 && (input[i] < 9)) || (input[i] != 32 && \
		input[i] > 12))
		{
			node = malloc(sizeof(t_args));
			if (!node)
				return (lexer_error(data, arg_list, NULL));
			set_arg_node(node);
			if (get_arg_node(data, node, input, &i) == 1)
				return (lexer_error(data, arg_list, node));
			arg_list = add_to_back_args(arg_list, node);
			data->args_len++;
		}
		if (input[i])
			i++;
		else
			break ;
	}
	return (arg_list);
}
