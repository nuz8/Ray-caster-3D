/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:37:49 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 08:54:48 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include <unistd.h>

#define MAX_FD 4096

char		*get_next_line(int fd);
static char	*ensure_data(int fd, char buffer[][BUFFER_SIZE + 1]);
static char	*extend_line(int fd, char *line, char buffer[][BUFFER_SIZE + 1]);
static char	*grow_line(int fd, char *line, char buffer[][BUFFER_SIZE + 1]);

char	*get_next_line(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	line = ensure_data(fd, buffer);
	if (!line)
		return (NULL);
	if (line[line_length(line) - 1] != '\n')
		line = extend_line(fd, line, buffer);
	return (line);
}

static char	*ensure_data(int fd, char buffer[][BUFFER_SIZE + 1])
{
	ssize_t	bytes_read;

	if (!buffer[fd][0])
	{
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		buffer[fd][bytes_read] = '\0';
	}
	return (copy_n_shift(buffer[fd]));
}

static char	*extend_line(int fd, char *line, char buffer[][BUFFER_SIZE + 1])
{
	ssize_t	bytes_read;

	while (line && line[line_length(line) - 1] != '\n')
	{
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
				return (free(line), NULL);
			return (line);
		}
		buffer[fd][bytes_read] = '\0';
		line = grow_line(fd, line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}

static char	*grow_line(int fd, char *line, char buffer[][BUFFER_SIZE + 1])
{
	char	*part;
	char	*joined;

	part = copy_n_shift(buffer[fd]);
	if (!part)
		return (free(line), NULL);
	joined = join_parts(line, part);
	if (!joined)
		return (free(line), free(part), NULL);
	return (joined);
}
