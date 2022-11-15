/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:23:25 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/05/12 15:23:54 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*remove_line(char *buffer)
{
	int		i;
	char	*l_buff;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	l_buff = ft_substr(buffer, i + 1, ft_strlen(buffer));
	free(buffer);
	return (l_buff);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_substr(buffer, 0, i + 1);
	else
	{
		line = ft_calloc(ft_strlen(buffer) + 1, sizeof(char));
		line = ft_memcpy(line, buffer, ft_strlen(buffer));
	}
	return (line);
}

static char	*read_line(int fd, char *buffer)
{
	int		read_count;
	char	*read_buffer;
	char	*l_buff;

	read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buffer)
		return (NULL);
	read_count = 1;
	while (!ft_strchr(buffer, '\n') && read_count != 0)
	{
		read_count = read(fd, read_buffer, BUFFER_SIZE);
		if (read_count == -1)
		{
			free(read_buffer);
			free(buffer);
			return (NULL);
		}
		read_buffer[read_count] = '\0';
		l_buff = buffer;
		buffer = ft_strjoin(l_buff, read_buffer);
		free(l_buff);
	}
	free(read_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buff[256];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buff[fd] = read_line(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = get_line(buff[fd]);
	buff[fd] = remove_line(buff[fd]);
	return (line);
}
