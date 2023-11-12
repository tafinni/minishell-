/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:42:49 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/11 19:17:00 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnondigitstr(char *str)
{
	int	index;

	index = 0;
	if (str[0] == '-')
	{
		if (ft_strlen(str) > 20 || (ft_strlen(str) == 20
				&& ft_strncmp(str, "-9223372036854775808", 20) > 0))
			return (FAIL);
	}
	else if (ft_strlen(str) > 19 || (ft_strlen(str) == 19
			&& ft_strncmp(str, "9223372036854775807", 19) > 0))
		return (FAIL);
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] != '\0')
	{
		if (ft_isdigit(str[index]))
			index++;
		else
			return (FAIL);
	}
	return (SUCCESS);
}

static void	free_exit(t_data *data)
{
	if (data->start_tokens)
		free_tokens(&data->start_tokens);
	if (data->env_arr)
		free_2d_str(data->env_arr);
	free_env_list(&data->env);
}

void	builtin_exit(t_data *data, char **args)
{
	int	status;

	status = g_ret_number;
	if (data->tokens_len == 1)
		ft_putstr_fd("exit\n", 1);
	if (args[1])
	{
		if (ft_isnondigitstr(args[1]) == FAIL)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			status = 255;
		}
		else if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_ret_number = 1;
			return ;
		}
		else
			status = (unsigned char)ft_atoi(args[1]);
	}
	free_exit(data);
	exit (status);
}
