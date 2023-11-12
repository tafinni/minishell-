/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:28:58 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 19:18:32 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_args(t_data *data, t_args *temp, t_token *new, int cmds)
{
	data->heredoc_sign = 0;
	if (data->redir_parser_check == 0 && data->found_command == 0)
		first_found_command(data, temp, new);
	if (data->error == 1)
		return (FAIL);
	if (cmds == 0)
	{
		first_str(data, temp, new);
		if (data->error == 1)
			return (FAIL);
		if (data->redir_parser_check == 1)
			return (0);
	}
	if (data->redir_parser_check == 0 && temp->redir == 0)
	{
		add_to_str(data, temp, new, cmds);
		return (1);
	}
	if (data->redir_parser_check == 1)
		return (0);
	else
		return (1);
}

static t_args	*make_token(t_data *data, t_args *temp, t_token *new, int i)
{
	int	cmds;

	cmds = 0;
	set_token(new);
	while (temp->pipe != 1)
	{
		data->redir_parser_check = 0;
		if (temp->redir != 0)
		{
			data->redir_parser_check = redir_parser_check(temp);
			if (has_redir(data, new, temp, i) == 1)
				data->error = 1;
			i++;
			str_redir_check(data, new, temp, &cmds);
			temp = temp->next;
		}
		else if (temp->pipe != 1 && data->error != 1)
			cmds += get_token_args(data, temp, new, cmds);
		if (temp->next == NULL || data->error == 1)
			break ;
		temp = temp->next;
	}
	return (temp);
}

static int	empty_cmd_check(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		if (temp->str)
		{
			if (ft_strlen(temp->str[0]) < 1 && ft_strlen(temp->str[1]) > 0)
			{
				move_str(&temp);
				if (ft_strlen(temp->cmd_str) < 1)
					new_cmd_str(&temp);
			}
			else if (ft_strlen(temp->str[0]) < 1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	get_tokens(t_data *data, t_token *tokens, t_args *args, int first_count)
{
	t_args	*temp;
	t_token	*new;

	data->tokens_len = 0;
	temp = args;
	while (temp != NULL)
	{
		data->found_command = 0;
		data->heredoc_sign = 0;
		new = malloc(sizeof(t_token));
		if (!new)
			return (parser_error(args, tokens, NULL));
		new->order = first_count++;
		temp = make_token(data, temp, new, 0);
		if (data->error == 1)
			return (parser_error(args, tokens, new));
		tokens = add_to_back_token(tokens, new);
		temp = temp->next;
	}
	data->start_tokens = tokens;
	data->tokens_len = first_count;
	free_args(&args);
	if (empty_cmd_check(tokens) == FAIL || data->error == 2)
		return (FAIL);
	return (0);
}
