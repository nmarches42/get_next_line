/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicco42 <nicco42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:57:40 by nicco42           #+#    #+#             */
/*   Updated: 2024/12/12 10:33:15 by nicco42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_and_append(fd, &remainder);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_and_append(int fd, char **remainder)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		if (*remainder && ft_strchr(*remainder, '\n'))
			return (free(buffer), extract_line(remainder));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read < 0)
				return (free(*remainder), *remainder = NULL, NULL);
			if (*remainder && **remainder)
				return (extract_line(remainder));
			return (free(*remainder), *remainder = NULL, NULL);
		}
		buffer[bytes_read] = '\0';
		*remainder = ft_strjoin(*remainder, buffer);
		if (!*remainder)
			return (free(buffer), NULL);
	}
}

char	*extract_line(char **remainder)
{
	char	*newline;
	char	*line;
	char	*new_remainder;
	size_t	len;

	newline = ft_strchr(*remainder, '\n');
	if (newline == NULL)
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		return (line);
	}
	len = newline - *remainder + 1;
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, *remainder, len + 1);
	new_remainder = ft_strdup(newline + 1);
	free(*remainder);
	*remainder = new_remainder;
	return (line);
}
