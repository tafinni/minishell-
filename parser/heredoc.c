/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:42 by tfinni            #+#    #+#             */
/*   Updated: 2023/09/12 19:27:35 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_doc(t_data *data, char **save, char **text, int fd)
{
	(*save) = ft_strjoin(*text, "\n");
	if (!(*save))
		ft_error(data, "malloc error\n", 0);
	if (write(fd, *save, ft_strlen(*save)) < 0)
		ft_error(data, "write error\n", 0);
	if ((*save) != NULL)
		free_str((*save));
}

static void	heredoc_loop(t_data *data, t_args *temp, int *fd)
{
	char			*text;
	char			*save;
	struct termios	t;

	while (g_ret_number != -2)
	{
		tcgetattr(STDIN_FILENO, &t);
		signal(SIGINT, handle_signal_heredoc);
		close_echoctl(&t);
		text = readline("> ");
		if (compare_str(temp->next->str, text) == 0)
		{
			if (text != NULL)
				free_str(text);
			break ;
		}
		else
			save_doc(data, &save, &text, *fd);
		if (text != NULL)
			free_str(text);
	}
	reset_echoctl(&t);
	close((*fd));
}

void	get_heredoc(t_data *data, t_token *new, t_args *temp, int i)
{
	char	*order;
	char	*saved_name;
	int		fd;

	new->infiles++;
	order = ft_itoa(new->order);
	if (!order)
		ft_error(data, "malloc error\n", 0);
	saved_name = ft_strjoin("heredoc_temp_", order);
	if (!saved_name)
		ft_error(data, "malloc error\n", 0);
	free(order);
	fd = open(saved_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		ft_error(data, "open error\n", 0);
	heredoc_loop(data, temp, &fd);
	new->redir_to[i] = ft_strdup(saved_name);
	if (!new->redir_to[i])
		ft_error(data, "malloc error\n", 0);
	free_str(saved_name);
	if (g_ret_number == -2)
	{
		data->error = 2;
		g_ret_number = 1;
	}
}
