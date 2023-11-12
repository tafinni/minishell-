/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:13:36 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 12:35:15 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char *str)
{
	free(str);
	str = NULL;
}

void	free_2d_str(char **str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return ;
	while (str[index] != NULL)
	{
		free(str[index]);
		str[index] = NULL;
		index++;
	}
	free(str);
	str = NULL;
}
