/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle_multiquote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:41:14 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/12 13:34:20 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes(t_data *data, char *tmp_line, int quote)
{
	char	quote_char;
	char	*trim_line;
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (quote == 1)
		quote_char = '\'';
	else if (quote == 2)
		quote_char = '\"';
	else
		return (tmp_line);
	trim_line = (char *)malloc(sizeof(char) * (ft_strlen(tmp_line) - 1));
	if (!trim_line)
		ft_error(data, "malloc error\n", 0);
	while (tmp_line[++i])
	{
		if (tmp_line[i] != quote_char)
			trim_line[len++] = tmp_line[i];
	}
	free_str(tmp_line);
	trim_line[len] = '\0';
	return (trim_line);
}

static void	calculate_segment_len(int quote, int *i,
	int *segment_len, char *tmp_line)
{
	while ((quote == 1 && tmp_line[++(*i)] != '\'')
		|| (quote == 2 && tmp_line[++(*i)] != '\"')
		|| (quote == 0 && tmp_line[++(*i)]
			&& tmp_line[*i] != '\"' && tmp_line[*i] != '\''))
		(*segment_len)++;
	if (quote)
	{
		(*i)++;
		(*segment_len)++;
	}
}

static char	**process_quoted_segments(t_data *data, t_args *args,
		int quote, int *i)
{
	int		segment_len;
	int		start;
	char	**segments;
	char	*quoted_segment;

	segment_len = 1;
	start = *i;
	segments = (char **)ft_calloc(sizeof(char *), 4);
	if (!segments)
		ft_error(data, "malloc error\n", 0);
	segments[0] = ft_substr(args->str, 0, *i);
	if (!segments[0])
		ft_error(data, "malloc error\n", 0);
	calculate_segment_len(quote, i, &segment_len, args->str);
	quoted_segment = ft_substr(args->str, start, segment_len);
	if (!quoted_segment)
		ft_error(data, "malloc error\n", 0);
	segments[1] = remove_quotes(data, quoted_segment, quote);
	if (quote != 1 && ft_strchr(segments[1], '$'))
		segments[1] = expand_variables_and_replace(data, segments[1]);
	segments[2] = ft_substr(args->str, *i, ft_strlen(args->str));
	if (!segments[2])
		ft_error(data, "malloc error\n", 0);
	return (segments);
}

void	expand_handle_multiquote(t_data *data, t_args *args, int *i,
		char quote_char)
{
	int		quote;
	char	**tmp_str;

	quote = 0;
	if (quote_char == '\'')
		quote = 1;
	else if (quote_char == '\"')
		quote = 2;
	tmp_str = process_quoted_segments(data, args, quote, i);
	*i = ft_strlen(tmp_str[0]) + ft_strlen(tmp_str[1]) - 1;
	free_str(args->str);
	args->str = join_strings(data, tmp_str, 3);
	free_2d_str(tmp_str);
}
