/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:05:33 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/11 18:47:04 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token(t_token *new)
{
	new->cmd_id = 0;
	new->cmd_str = NULL;
	new->str = NULL;
	new->redir_to = NULL;
	new->file = NULL;
	new->infiles = 0;
	new->outfiles = 0;
	new->str_len = 0;
	new->in = 0;
	new->out = 1;
	new->error = 0;
}

int	compare_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str2[i] == str1[i] && str2[i] != '\0' && str1[i] != '\0')
	{
		if (str2[i] != str1[i])
			return (1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	else
		return (1);
}

int	cmd_id(t_token *new)
{
	if (compare_str(new->cmd_str, "echo") == 0)
		return (ECHO_CMD);
	else if (compare_str(new->cmd_str, "cd") == 0)
		return (CD);
	else if (compare_str(new->cmd_str, "export") == 0)
		return (EXPORT);
	else if (compare_str(new->cmd_str, "unset") == 0)
		return (UNSET);
	else if (compare_str(new->cmd_str, "env") == 0)
		return (ENV);
	else if (compare_str(new->cmd_str, "exit") == 0)
		return (EXIT);
	else if (compare_str(new->cmd_str, "pwd") == 0)
		return (PWD);
	else
		return (0);
}

t_token	*add_to_back_token(t_token *list, t_token *new)
{
	t_token	*last;

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

int	parser_error(t_args *args, t_token *tokens, t_token *node)
{
	ft_putstr_fd("minishell: parser error\n", 2);
	if (args != NULL)
		free_args(&args);
	if (tokens != NULL)
		free_tokens(&tokens);
	if (node != NULL)
		free_tokens(&node);
	return (1);
}
