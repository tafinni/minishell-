/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:28:07 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/11 18:32:00 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	saved_to_res(t_data *data, char **res, int i, char **saved)
{
	if (!res[i])
		ft_error(data, "malloc error\n", 0);
	(*saved) = ft_strdup(res[i]);
	free_str(res[i]);
}

char	*found_path(char **to_check, char *res)
{
	free_2d_str(to_check);
	return (res);
}

t_env	*search_env_for_path(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, "PATH", 4) == 0)
			break ;
		temp = temp->next;
	}
	return (temp);
}
