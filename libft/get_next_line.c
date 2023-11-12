/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:28:35 by tfinni            #+#    #+#             */
/*   Updated: 2023/01/14 21:02:47 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_line(char *buffer)
{
	char		*line;
	int			i;

	i = 0;
	if (!*buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_newtext(char *text)
{
	int		i;
	int		y;
	char	*newtext;

	i = 0;
	y = 0;
	while (text[i] != '\0' && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free(text);
		return (NULL);
	}
	newtext = malloc(sizeof(char) * (ft_strlen(text) - i) + 1);
	if (!newtext)
		return (NULL);
	i++;
	while (text[i] != '\0')
		newtext[y++] = text[i++];
	newtext[y] = '\0';
	if (*text)
		free(text);
	return (newtext);
}

static char	*ft_readuntil(int fd, char *text, char *buffer)
{
	int	rsize;

	rsize = 1;
	while (rsize != 0 && ft_strchr(text, '\n') == NULL)
	{
		rsize = read(fd, buffer, BUFFER_SIZE);
		if (rsize < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[rsize] = '\0';
		text = ft_getstrjoin(text, buffer);
	}
	free(buffer);
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;
	char		*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!text)
	{
		text = malloc(sizeof(char) * 1);
		if (!text)
		{
			free(buffer);
			return (NULL);
		}
		*text = '\0';
	}
	text = ft_readuntil(fd, text, buffer);
	if (!text)
		return (NULL);
	line = ft_line(text);
	text = ft_newtext(text);
	return (line);
}
