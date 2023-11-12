/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:47:58 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/11 18:29:48 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_non_arg(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (ft_strncmp(tmp->value, "", 1) != 0)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd("\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

t_env	*create_new_env(char *name, char *value)
{
	t_env	*new; 

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
	{
		ft_putstr_fd("minishell: malloc error\n", 2);
		return (NULL);
	}
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	add_env_argument(t_data *data, t_env **env_list, char *arg)
{
	char	**env_string;
	t_env	*new;
	int		non_value;

	non_value = 0;
	if (ft_strchr(arg, '='))
		non_value = 1;
	env_string = ft_split_env(data, arg, '=');
	if (!env_string)
		ft_error(data, "malloc error\n", 0);
	if (non_value == 0)
	{
		if (env_string[1] == NULL)
			env_string[1] = ft_strdup("");
	}
	if (find_replace_env(env_string[0], env_string[1],
			env_list, non_value) == FAIL)
	{
		new = create_new_env(env_string[0], env_string[1]);
		if (!new)
			ft_error(data, "malloc error\n", 0);
		add_to_back_env(env_list, new);
	}
	if (env_string != NULL)
		free_2d_str(env_string);
}

void	builtin_export(t_data *data, char **arg, t_env **env_list)
{
	int	index;

	index = 1;
	g_ret_number = 0;
	if (!arg[1])
	{
		export_non_arg(env_list);
		return ;
	}
	while (arg[index])
	{
		if (check_envvar_name_export(arg[index]) == FAIL)
		{
			g_ret_number = 1;
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg[index], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		else
		{
			add_env_argument(data, env_list, arg[index]);
		}
		index++;
	}
}
