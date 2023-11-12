/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:02:17 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 15:34:50 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flag_six(void)
{
	ft_putstr_fd(": filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	g_ret_number = 2;
}

void	ft_error(t_data *data, char *str, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	g_ret_number = 1;
	if (flag == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (flag == 2)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (flag == 3)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (flag == 4)
		ft_putstr_fd(": is a directory\n", 2);
	else if (flag == 5)
		ft_putstr_fd(": Not a directory\n", 2);
	else if (flag == 6)
		flag_six();
	if (flag == 1 || flag == 3)
		g_ret_number = 127;
	else if (flag == 2 || flag == 4 || flag == 5)
		g_ret_number = 126;
	if (data->tokens_len > 1)
		free_tokens(&data->start_tokens);
	if (data->env)
		free_env_list(&data->env);
	exit(g_ret_number);
}

int	args_len(t_args *args)
{
	t_args	*temp;
	int		i;

	i = 0;
	temp = args;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	redir_error(t_args *temp)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (temp->redir == L_ONE)
		ft_putstr_fd("<'\n", 2);
	else if (temp->redir == L_TWO)
		ft_putstr_fd("<<'\n", 2);
	else if (temp->redir == R_ONE)
		ft_putstr_fd(">'\n", 2);
	else if (temp->redir == R_TWO)
		ft_putstr_fd(">>'\n", 2);
	else if (temp->pipe == 1)
		ft_putstr_fd("|'\n", 2);
	return (-1);
}

int	cmd_str_check(t_token *temp)
{
	int		i;
	char	*str;

	i = 0;
	str = temp->str[0];
	while (str[i])
	{
		if (str[i] == '/')
			return (3);
		i++;
	}
	if (temp->cmd_id > 0)
		return (1);
	else 
		return (2);
	return (0);
}
