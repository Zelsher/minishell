/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboumaza <eboumaza.trav@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:05:44 by eboumaza          #+#    #+#             */
/*   Updated: 2023/09/12 22:05:44 by eboumaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_adder(char *line, char *buffer)
{
	char	*newline;

	if (!line && buffer[0] != '\0')
		newline = ft_strdup(buffer);
	else if (buffer && buffer[0] != '\0')
		newline = ft_strjoin(line, buffer);
	else
		return (line);
	if (line)
		free(line);
	if (!newline)
		return (NULL);
	return (newline);
}

char	*ft_read_line(int fd, char *buffer, char *line)
{
	int		verif;

	verif = 1;
	while (verif > 0)
	{
		verif = read(fd, buffer, BUFFER_SIZE);
		if (verif < 0)
		{
			if (line)
				free(line);
			free(buffer);
			return (NULL);
		}
		buffer[verif] = '\0';
		if (verif == 0)
			break ;
		line = ft_adder(line, buffer);
		if (!line || ft_strchr(line, '\n'))
			break ;
	}
	free(buffer);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_linator(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		i++;
		if (buffer[i - 1] == '\n')
			break ;
	}
	return (line);
}

char	*ft_buffinator(char *buffer)
{
	size_t	malloc_len;
	size_t	i;
	char	*temp;

	malloc_len = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[1 + i])
	{
		while (buffer[malloc_len + i])
			malloc_len++;
	}
	if (malloc_len > 0)
	{
		temp = malloc(sizeof(char) * (malloc_len));
		if (!temp)
			return (NULL);
		ft_strcpy(temp, buffer + i + 1);
	}
	else
		temp = NULL;
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer[100];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	buffer[fd] = ft_read_line(fd, temp, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_linator(buffer[fd]);
	buffer[fd] = ft_buffinator(buffer[fd]);
	return (line);
}
