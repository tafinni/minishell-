/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:32:37 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/11 18:28:53 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_list_len(t_env *env)
{
	int		counter;
	t_env	*temp;

	temp = env;
	counter = 0;
	while (temp != NULL)
	{
		counter++;
		temp = temp->next;
	}
	return (counter);
}

char	**get_env_arr(t_data *data, int i)
{
	t_env	*temp;
	char	**res;
	char	*saved;

	temp = data->env;
	res = NULL;
	res = malloc(sizeof(char *) * (env_list_len(data->env) + 1));
	if (!res)
		return (NULL);
	while (temp != NULL)
	{
		res[i] = ft_strdup(temp->name);
		saved_to_res(data, res, i, &saved);
		res[i] = ft_strjoin(saved, "=");
		free_str(saved);
		saved_to_res(data, res, i, &saved);
		res[i] = ft_strjoin(saved, temp->value);
		if (!res[i])
			ft_error(data, "malloc error\n", 0);
		free_str(saved);
		temp = temp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*find_path(t_data *data, t_env *env, char *check_str, int i)
{
	char	*res;
	char	**to_check;
	t_env	*temp;

	if (!check_str)
		return (NULL);
	temp = search_env_for_path(env);
	if (temp == NULL)
		return (NULL);
	to_check = ft_split(temp->value, ':');
	if (!to_check)
		ft_error(data, "malloc error\n", 0);
	while (to_check[++i])
	{
		res = ft_strjoin(to_check[i], check_str);
		if (!res)
			ft_error(data, "malloc error\n", 0);
		if (access(res, X_OK) == 0)
			return (found_path(to_check, res));
		free_str(res);
	}
	free_str(check_str);
	free_2d_str(to_check);
	return (NULL);
}
