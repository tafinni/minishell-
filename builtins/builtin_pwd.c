/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:15:34 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/04 19:00:56 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)))
	{
		g_ret_number = 0;
		printf("%s\n", buffer);
	}
	else
	{
		printf(".\n");
		g_ret_number = 1;
	}
}
