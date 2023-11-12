/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:15:15 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/11 11:52:02 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_env *env_list, char **arg)
{
	t_env	*new;

	if (arg[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	new = env_list;
	while (new)
	{
		if (new->name && new->value && ft_strncmp(new->value, "", 1) != 0)
		{
			ft_putstr_fd(new->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(new->value, 1);
			ft_putstr_fd("\n", 1);
		}
		new = new->next;
	}
	g_ret_number = 0;
}
