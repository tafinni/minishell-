/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:07:16 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/11 18:46:46 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_found_command(t_data *data, t_args *temp, t_token *new)
{
	new->cmd_str = ft_strdup(temp->str);
	if (!new->cmd_str)
		data->error = 1;
	if (data->error != 1)
	{
		new->cmd_id = cmd_id(new);
		data->found_command = 1;
	}
}

void	first_str(t_data *data, t_args *temp, t_token *new)
{
	int	i;

	i = 0;
	if (new->str != NULL)
		free_2d_str(new->str);
	new->str = malloc(sizeof(char *) * (data->args_len + 1));
	if (!new->str)
		data->error = 1;
	if (data->error != 1)
	{
		while (i < data->args_len)
		{
			new->str[i] = NULL;
			i++;
		}
		new->str[0] = ft_strdup(temp->str);
		if (!new->str[0])
			data->error = 1;
		if (data->error != 1)
			new->str[1] = NULL;
	}
}

void	add_to_str(t_data *data, t_args *temp, t_token *new, int cmds)
{
	if (cmds == 0 && new->str[cmds])
		free_str(new->str[cmds]);
	new->str[cmds] = ft_strdup(temp->str);
	if (!new->str)
		data->error = 1;
	if (data->error != 1)
	{
		new->str[cmds + 1] = NULL;
		new->str_len++;
	}
}

void	move_str(t_token **token)
{
	int	i;

	i = 0;
	while (i < (*token)->str_len)
	{
		free_str((*token)->str[i]);
		if ((*token)->str[i + 1])
			(*token)->str[i] = ft_strdup((*token)->str[i + 1]);
		else
			(*token)->str[i] = NULL;
		i++;
	}
	(*token)->str[i] = NULL;
}

void	new_cmd_str(t_token **token)
{
	if ((*token)->cmd_str)
		free_str((*token)->cmd_str);
	(*token)->cmd_str = ft_strdup((*token)->str[0]);
}
