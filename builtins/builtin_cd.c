/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:23:32 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/04 16:22:46 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char **arg, t_env *env_list)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		find_replace_env("OLDPWD", buffer, &env_list, 1);
	if (arg[1] == NULL || ft_strlen(arg[1]) < 1)
	{
		if (chdir(get_environment("HOME", env_list)) != 0)
		{
			g_ret_number = 1;
			ft_putstr_fd("minishell: HOME not set\n", 2);
			return ;
		}
	}
	else if (chdir(arg[1]) != 0)
	{
		g_ret_number = 1;
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		find_replace_env("PWD", buffer, &env_list, 1);
	g_ret_number = 0;
}
