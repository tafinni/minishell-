/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:50:19 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/04 17:13:22 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_env_arg(t_env **env, t_env *current, t_env *previous)
{
	char	*env_name;
	char	*env_value;

	env_name = (char *)current->name;
	env_value = (char *)current->value;
	if (previous == NULL)
		*env = (*env)->next;
	else
		previous->next = current->next;
	free(env_name);
	free(env_value);
	free(current);
}

static int	find_env_arg(char *find_str, t_env **current,
			t_env **previous, int *flag_found_env)
{
	char	*env_name;

	env_name = (char *)(*current)->name;
	if (env_name && ft_strncmp(find_str, env_name, ft_strlen(find_str)) == 0)
	{
		*flag_found_env = 1;
		return (SUCCESS);
	}
	else
	{
		*previous = *current;
		*current = (*current)->next;
		g_ret_number = 0;
		return (FAIL);
	}
}

static int	check_envvar_name(char *str)
{
	int	index;

	index = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		g_ret_number = 1;
		return (FAIL);
	}
	while (str[index] != '\0')
	{
		if (str[index] == '=')
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			g_ret_number = 1;
			return (FAIL);
		}
		index++;
	}
	return (SUCCESS);
}

void	builtin_unset(char **arg, t_env **env_list)
{
	int		index;
	int		flag_found_env;
	t_env	*current;
	t_env	*previous;

	index = 1;
	while (arg[index])
	{
		flag_found_env = 0;
		current = *env_list;
		previous = NULL;
		while (current)
		{
			if (check_envvar_name(arg[index]) == FAIL)
				break ;
			if (find_env_arg(arg[index], &current, &previous,
					&flag_found_env) == SUCCESS)
				break ;
		}
		if (current && flag_found_env == 1)
			delete_env_arg(env_list, current, previous);
		index++;
	}
	if (!arg[1])
		g_ret_number = 0;
}
