/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:58:23 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/13 11:41:20 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_newline(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_char(int fd)
{
	char		*buf;
	long long	ret;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	ret = read(fd, (void *)buf, BUFFER_SIZE);
	if (ret <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[ret] = 0;
	return (buf);
}

char	*fill_line(int fd, char **stash, int reset)
{
	char		*new_line;
	char		*temp;
	static int	tour = 0;

	if (reset)
		tour = 0;
	if (tour == 0)
	{
		*stash = get_next_char(fd);
		if (!*stash)
			return (NULL);
		tour++;
		return (*stash);
	}
	else
	{
		temp = get_next_char(fd);
		if (!temp)
			return (NULL);
		new_line = ft_strjoin_gnl(*stash, temp);
		free(temp);
		free(*stash);
		*stash = new_line;
		return (new_line);
	}
}

char	*get_next_line(int fd, int reset)
{
	static char	*stash = NULL;
	char		*line;
	char		*new_line;

	if (reset)
		stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = fill_line(fd, &stash, reset);
	while (line && !check_newline(line))
		line = fill_line(fd, &stash, reset);
	if (!line)
	{
		if (!stash || !stash[0])
		{
			free(stash);
			return (NULL);
		}
		new_line = ft_strdup_newline(stash, &stash, 1);
		return (new_line);
	}
	new_line = ft_strdup_newline(line, &stash, 1);
	return (new_line);
}
