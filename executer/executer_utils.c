/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:44:22 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/13 14:56:16 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	one_builtin(t_data *data, t_token *temp, int in, int out)
{
	if (data->tokens_len == 1 && temp->cmd_id > 0 && temp->error == 0)
	{
		dup_and_close(temp, &in, &out, 1);
		builtins(data, temp, data->env);
		dup_and_close(temp, &in, &out, 2);
		return (1);
	}
	else if (temp->error == 1)
		return (0);
	return (0);
}

void	waitprocesses(t_data *data, int *process)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < data->tokens_len)
	{
		if (process[i])
			waitpid(process[i], &status, 0);
		i++;
	}
	if (process[i - 1])
	{
		if (WIFEXITED(status))
			g_ret_number = WEXITSTATUS(status);
		else if (!WIFSIGNALED(status))
			g_ret_number = status;
	}
	free(process);
}

int	create_processes(t_data *data, int *process, int position)
{
	process[position] = fork();
	if (process[position] == -1)
		ft_error(data, "fork error\n", 0);
	return (process[position]);
}

void	handle_end(t_data *data, t_token *temp)
{
	free_2d_str(data->env_arr);
	close(temp->in);
	close(temp->out);
}

void	dup_and_close(t_token *temp, int *in, int *out, int flag)
{
	if (flag == 1)
	{
		(*in) = dup(0);
		(*out) = dup(1);
		dup2(temp->in, 0);
		close(temp->in);
		dup2(temp->out, 1);
		close(temp->out);
	}
	else if (flag == 2)
	{
		dup2((*in), 0);
		close((*in));
		dup2((*out), 1);
		close((*out));
	}
}
