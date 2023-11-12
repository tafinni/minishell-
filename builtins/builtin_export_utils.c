/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:58:51 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/04 15:16:11 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_equal_sign(char *arg, int i, char c)
{
	while (arg[i])
	{
		if (arg[i] == c)
			return (1);
		else
			i--;
	}
	return (0);
}

int	check_envvar_name_export(char *str)
{
	int	index;

	index = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		return (FAIL);
	}
	while (str[index])
	{
		if (!(ft_isalnum(str[index]) || ft_isalpha(str[index])
				|| str[index] == '_')
			&& is_equal_sign(str, index, '=') == 0)
			return (FAIL);
		index++;
	}
	return (SUCCESS);
}
