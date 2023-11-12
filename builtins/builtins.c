/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:27:44 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 18:46:15 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_data *data, t_token *token, t_env *env_list)
{
	if (token->cmd_id == ECHO_CMD)
		builtin_echo(data, token->str, 1);
	else if (token->cmd_id == PWD)
		builtin_pwd();
	else if (token->cmd_id == ENV)
		builtin_env(env_list, token->str);
	else if (token->cmd_id == CD)
		builtin_cd(token->str, env_list);
	else if (token->cmd_id == EXPORT)
		builtin_export(data, token->str, &env_list);
	else if (token->cmd_id == UNSET)
		builtin_unset(token->str, &env_list);
	else if (token->cmd_id == EXIT)
		builtin_exit(data, token->str);
	else
		return (0);
	return (1);
}
