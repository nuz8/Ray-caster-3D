/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:41:05 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 12:44:25 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*copy_n_shift(char *buffer)
{
	size_t	len;
	size_t	i;
	char	*line;

	if (!buffer)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = duplicate_segment(buffer, len);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[len + i])
	{
		buffer[i] = buffer[len + i];
		i++;
	}
	buffer[i] = '\0';
	return (line);
}

size_t	line_length(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*duplicate_segment(char *buffer, size_t length)
{
	char	*segment;
	size_t	i;

	segment = malloc(length + 1);
	if (!segment)
		return (NULL);
	i = 0;
	while (i < length)
	{
		segment[i] = buffer[i];
		i++;
	}
	segment[length] = '\0';
	return (segment);
}
