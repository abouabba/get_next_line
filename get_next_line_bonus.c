/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:01:37 by abouabba          #+#    #+#             */
/*   Updated: 2024/12/09 11:17:39 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*check_read(int fd, char *buffer)
{
	char			*temp;
	ssize_t			read_bytes;

	if (BUFFER_SIZE > INT_MAX)
		return (NULL);
	temp = malloc((size_t)BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (1)
	{
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		temp[read_bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_next(char *buffer)
{
	char	*new_buffer;
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = ft_strdup(buffer + i + 1);
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

char	*get_the_line(char *buffer)
{
	char	*retu;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && (buffer[i] != '\n'))
	{
		i++;
	}
	retu = malloc(i + 2);
	if (!retu)
		return (NULL);
	while (j < i)
	{
		retu[j] = buffer[j];
		j++;
	}
	if (buffer[i] == '\n')
		retu[i++] = '\n';
	retu[i] = '\0';
	return (retu);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX || read(fd, NULL, 0) < 0)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	buffer[fd] = check_read(fd, buffer[fd]);
	if (!buffer[fd] || buffer[fd][0] == '\0')
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	line = get_the_line(buffer[fd]);
	buffer[fd] = get_next(buffer[fd]);
	return (line);
}