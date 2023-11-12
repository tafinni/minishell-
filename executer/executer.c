/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:08:42 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/13 13:44:01 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_path(t_data *data, t_token *temp)
{
	char	*path;

	path = find_path(data, data->env, ft_strjoin("/", temp->cmd_str), 0);
	if (path == NULL)
		ft_error(data, temp->cmd_str, 1);
	temp->out = 1;
	if (execve(path, temp->str, data->env_arr) == -1)
	{
		if (errno == EACCES && compare_str(temp->cmd_str, ".") == 0)
			ft_error(data, temp->cmd_str, 6);
		else
			ft_error(data, temp->cmd_str, 1);
	}
	free(path);
}

static void	yes_path(t_data *data, t_token *temp)
{
	struct stat	s;

	if (access(temp->cmd_str, X_OK) != 0)
		ft_error(data, temp->cmd_str, 2);
	if (stat(temp->cmd_str, &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
			ft_error(data, temp->cmd_str, 4);
		else if (S_ISREG(s.st_mode))
		{
			if (execve(temp->cmd_str, temp->str, data->env_arr) == -1)
				ft_error(data, temp->cmd_str, 3);
		}
	}
}

static int	execute_command(t_data *data, t_token *temp)
{
	int	flag;

	set_in_out(temp);
	flag = cmd_str_check(temp);
	if (flag == 1)
		builtins(data, temp, data->env);
	else if (flag == 2)
		no_path(data, temp);
	else if (flag == 3)
	{
		if (access(temp->cmd_str, F_OK) == 0)
			yes_path(data, temp);
		else
			ft_error(data, temp->cmd_str, 3);
	}
	exit (g_ret_number);
}

static void	handle_new_process(t_data *data, t_token *temp, \
int position, int *fd)
{
	if (position < data->tokens_len - 1)
		close(fd[0]);
	execute_command(data, temp);
}

int	run_list(t_data *data, t_token *tokens, int position, int *process)
{
	t_token	*temp;
	int		fd[2];

	process = malloc(sizeof(int) * data->tokens_len);
	if (!process)
		ft_error(data, "malloc error\n", 0);
	temp = tokens;
	while (temp && ++position < data->tokens_len)
	{
		set_signal_child();
		if (get_output_input(data, temp, position, fd) != -1 && \
		one_builtin(data, temp, 0, 0) == 1)
		{
			free(process);
			return (1);
		}
		data->env_arr = get_env_arr(data, 0);
		if (create_processes(data, process, position) == 0)
			handle_new_process(data, temp, position, fd);
		handle_end(data, temp);
		temp = temp->next;
	}
	waitprocesses(data, process);
	return (0);
}
