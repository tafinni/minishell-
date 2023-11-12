/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:36:09 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/05 16:15:47 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_env(t_data *data, char const *s, char c)
{
	char	**str_arr;
	size_t	len;

	str_arr = (char **)ft_calloc(sizeof(char *), (2 + 1));
	if (!str_arr)
		ft_error(data, "malloc error\n", 0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			str_arr[0] = ft_substr(s - len, 0, len);
			if (!str_arr[0])
				ft_error(data, "malloc error\n", 0);
			str_arr[1] = ft_substr(s - len, len + 1, ft_strlen(s));
			if (!str_arr[1])
				ft_error(data, "malloc error\n", 0);
			break ;
		}
		else
			s++;
	}
	return (str_arr);
}
