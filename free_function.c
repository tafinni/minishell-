/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:23:32 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/11 18:14:32 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **token)
{
	t_token	*lst;

	if (!token)
		return ;
	while ((*token) != NULL)
	{
		lst = (*token)->next;
		if ((*token)->cmd_str != NULL)
			free_str((*token)->cmd_str);
		if ((*token)->redir_to != NULL)
			free_2d_str((*token)->redir_to);
		if ((*token)->str != NULL)
			free_2d_str((*token)->str);
		if ((*token)->file != NULL)
			free((*token)->file);
		free(*token);
		*token = lst;
	}
}

void	free_args(t_args **args)
{
	t_args	*lst;

	if (!args)
		return ;
	while ((*args) != NULL)
	{
		lst = (*args)->next;
		free((*args)->str);
		free(*args);
		*args = lst;
	}
}

void	free_env_list(t_env **env_list)
{
	t_env	*lst;

	if (!env_list)
		return ;
	while ((*env_list) != NULL)
	{
		lst = (*env_list)->next;
		free((*env_list)->name);
		free((*env_list)->value);
		free(*env_list);
		*env_list = lst;
	}
}

static void	delete_heredocs(t_data *data, char *name)
{
	int		i;
	char	*order;

	i = 0;
	while (i < data->tokens_len)
	{
		order = ft_itoa(i);
		if (!order)
			ft_error(data, "malloc error", 0);
		name = ft_strjoin("heredoc_temp_", order);
		if (!name)
			ft_error(data, "malloc error", 0);
		unlink(name);
		free_str(order);
		free_str(name);
		i++;
	}
}

void	free_prompt(char *input, t_data *data)
{
	if (data->start_tokens != NULL)
		free_tokens(&data->start_tokens);
	if (input != NULL)
	{
		free(input);
		input = NULL;
	}
	delete_heredocs(data, "heredoc_temp_");
}
