/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:41:00 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 12:41:48 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redir_str(t_args *node)
{
	char	*res;

	res = NULL;
	if (node->redir == L_ONE)
		res = ft_strdup("<");
	else if (node->redir == L_TWO)
		res = ft_strdup("<<");
	else if (node->redir == R_ONE)
		res = ft_strdup(">");
	else if (node->redir == R_TWO)
		res = ft_strdup(">>");
	return (res);
}

static char	*str_when_pipe(t_data *data, char **new)
{
	(*new) = ft_strdup("|");
	data->prev_pipe = 0;
	return ((*new));
}

char	*ft_node_str(t_data *data, char *input, int start, int len)
{
	int		i;
	char	*new;

	i = 0;
	if (start == -1)
		start = 0;
	if (data->prev_pipe == 2)
		return (str_when_pipe(data, &new));
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	if (data->prev_pipe == 1)
	{
		len--;
		if (start != 0)
			start++;
	}
	while (i < len)
	{
		new[i] = input[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}
