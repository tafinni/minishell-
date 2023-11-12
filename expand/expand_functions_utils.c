/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_functions_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:23:07 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/05 16:28:29 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_g_ret_number(t_data *data, char *str)
{
	char	*result;
	char	*status;

	result = NULL;
	status = NULL;
	status = ft_itoa((unsigned int) g_ret_number);
	if (!status)
	{
		ft_error(data, "malloc error\n", 0);
	}
	result = ft_strjoin(status, str + 1);
	if (!result)
	{
		ft_error(data, "malloc error\n", 0);
	}
	free(status);
	status = NULL;
	free(str);
	str = NULL;
	return (result);
}

char	*replace_env_value(t_data *data, char *input_str,
			t_env *env_list, int *changed)
{
	char	*str_tail;
	int		len_env_name;

	str_tail = NULL;
	len_env_name = 0;
	while (env_list)
	{
		len_env_name = ft_strlen(env_list->name);
		if (ft_strnstr(input_str, env_list->name, len_env_name)
			&& !ft_isalnum(input_str[len_env_name]))
		{
			str_tail = ft_substr(input_str, len_env_name, ft_strlen(input_str));
			if (!str_tail)
				ft_error(data, "malloc error\n", 0);
			free(input_str);
			input_str = ft_strjoin(env_list->value, str_tail);
			if (!input_str)
				ft_error(data, "malloc error\n", 0);
			free(str_tail);
			*changed = 1;
			break ;
		}
		env_list = env_list->next;
	}
	return (input_str);
}

char	*replace_env_variables(t_data *data, char *input_str)
{
	char	*modified_str;
	int		changed;

	changed = 0;
	input_str = replace_env_value(data, input_str, data->env, &changed);
	modified_str = input_str;
	if (changed == 0)
	{
		while (input_str)
		{
			if (!ft_isalnum(*input_str))
			{
				input_str = ft_strdup(input_str);
				if (!input_str)
					ft_error(data, "malloc error\n", 0);
				free(modified_str);
				break ;
			}
			input_str++;
		}
	}
	return (input_str);
}

char	**split_replace(t_data *data, char **split_str, int *i, char *tmp)
{
	while (split_str[++(*i)])
	{
		if (split_str[*i][0] == '?')
			split_str[*i] = handle_g_ret_number(data, split_str[*i]);
		else if (ft_isdigit(split_str[*i][0]) || split_str[*i][0] == '!'
				|| split_str[*i][0] == '@' || split_str[*i][0] == '_')
		{
			tmp = split_str[*i];
			split_str[*i] = ft_substr(tmp, 1, ft_strlen(tmp));
			if (!split_str[*i])
				ft_error(data, "malloc error\n", 0);
			free(tmp);
		}
		else if (!ft_isalnum(split_str[*i][0]))
		{
			tmp = split_str[*i];
			split_str[*i] = ft_strjoin("$", tmp);
			if (!split_str[*i])
				ft_error(data, "malloc error\n", 0);
			free(tmp);
		}
		else
			split_str[*i] = replace_env_variables(data, split_str[*i]);
	}
	return (split_str);
}
