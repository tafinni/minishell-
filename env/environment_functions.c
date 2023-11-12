/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:36:29 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/11 17:38:40 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_replace_env(char *env_name, char *env_value, 
			t_env **env_list, int non_value)
{
	t_env	*new;
	size_t	len;

	new = *env_list;
	while (new)
	{
		len = ft_strlen(new->name);
		if (len == ft_strlen(env_name)
			&& ft_strncmp(env_name, new->name, (int)len) == 0)
		{
			if (ft_strncmp(env_value, "", 1) == 0 && non_value == 0)
				return (-1);
			if (new->value != NULL)
				free_str(new->value);
			new->value = ft_strdup(env_value);
			return (SUCCESS);
		}
		new = new->next;
	}
	return (FAIL);
}

char	*get_environment(char *find_name, t_env *env_list)
{
	t_env	*new;

	new = env_list;
	while (new)
	{
		if (ft_strncmp(find_name, new->name, ft_strlen(find_name)) == 0)
		{
			return (new->value);
		}
		new = new->next;
	}
	return (NULL);
}

t_env	**add_to_back_env(t_env **list, t_env *new)
{
	t_env	*last;

	if (!(*list))
	{
		*list = new;
		(*list)->next = NULL;
	}
	else
	{
		last = *list;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		last = last->next;
		last->next = NULL;
	}
	return (list);
}

void	init_env(char **env, t_env **env_list)
{
	int		index;
	char	**string_env;
	t_env	*new;

	index = 0;
	while (env[index])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return ;
		string_env = ft_split(env[index], '=');
		if (!string_env)
			return ;
		if (string_env && string_env[0] && string_env[1])
		{
			if (string_env[0] != NULL)
				new->name = ft_strdup(string_env[0]);
			if (string_env[1] != NULL)
				new->value = ft_strdup(string_env[1]);
			new->next = NULL;
			add_to_back_env(env_list, new);
		}
		free_2d_str(string_env);
		index++;
	}
}
