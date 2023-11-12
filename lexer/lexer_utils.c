/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:05:13 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/08 17:00:54 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_arg_node(t_args *node)
{
	node->str = NULL;
	node->quote = 0;
	node->redir = 0;
	node->pipe = 0;
	node->expand = 0;
}

int	check_space(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	else
		return (0);
}

t_args	*add_to_back_args(t_args *list, t_args *new)
{
	t_args	*last;

	if (!list)
	{
		list = new;
		list->next = NULL;
	}
	else
	{
		last = list;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		last = last->next;
		last->next = NULL;
	}
	return (list);
}

t_args	*lexer_error(t_data *data, t_args *args, t_args *node)
{
	t_args	*temp;

	while (args != NULL)
	{
		temp = args->next;
		free(args->str);
		args->str = NULL;
		free(args);
		args = temp;
	}
	if (node != NULL)
		free(node);
	data->tokens_len = 0;
	data->start_tokens = NULL;
	return (NULL);
}

void	lexer_msg(char token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token == '\"')
		ft_putstr_fd("\"'\n", 2);
	else if (token == '\'')
		ft_putstr_fd("\'\n", 2);
}
