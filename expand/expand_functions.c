/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:23:21 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 14:57:47 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_strings(t_data *data, char **string_array, int array_length)
{
	char	*result;
	int		index;
	char	*tmp;

	index = 0;
	result = ft_strdup("");
	if (!result)
		ft_error(data, "malloc error\n", 0);
	while (index < array_length)
	{
		tmp = result; 
		result = ft_strjoin(tmp, string_array[index]);
		if (!result)
		{
			ft_error(data, "malloc error\n", 0);
		}
		free(tmp);
		index++;
	}
	return (result);
}

static char	*merge_strings(t_data *data, char **string_array, int index)
{
	char	*merged_string;

	if (index == 0)
	{
		merged_string = ft_strdup("$");
		if (!merged_string)
		{
			ft_error(data, "malloc error\n", 0);
		}
	}
	else
	{
		merged_string = join_strings(data, string_array, index);
	}
	free_2d_str(string_array);
	return (merged_string);
}

char	*expand_variables_and_replace(t_data *data, char *str)
{
	char	**split_strings;
	int		index;

	index = -1;
	split_strings = ft_split(str, '$');
	if (!split_strings)
	{
		ft_error(data, "malloc error\n", 0);
	}
	if (str[0] != '$')
		index = 0;
	split_strings = split_replace(data, split_strings, &index, NULL);
	free(str);
	return (merge_strings(data, split_strings, index));
}

void	expand_args(t_data *data, t_args *arg_list)
{
	int	index;

	while (arg_list != NULL)
	{
		index = -1;
		if (arg_list->quote)
		{
			while (arg_list->str[++index])
			{
				expand_handle_multiquote(data, arg_list, &index,
					arg_list->str[index]);
				if (index == -1)
					break ;
			}
		}
		else if (ft_strchr(arg_list->str, '$'))
		{
			arg_list->str = expand_variables_and_replace(data, arg_list->str);
		}
		arg_list = arg_list->next;
	}
}
