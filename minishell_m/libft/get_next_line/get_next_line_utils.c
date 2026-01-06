/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mai <mai@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:58:23 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/13 11:33:12 by mai              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(char *src)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = malloc(ft_strlen_gnl(src, 0) + 1);
	if (!copy)
		return (NULL);
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	*ft_strdup_newline(char *src, char **stash, int type)
{
	size_t	i;
	char	*copy;
	char	*temp;

	i = 0;
	copy = malloc(ft_strlen_gnl(src, type) + 1);
	if (!copy)
		return (NULL);
	while (src[i] && src[i] != '\n')
	{
		copy[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
		copy[i++] = '\n';
	copy[i] = 0;
	temp = ft_strdup_gnl(&(*stash)[i]);
	free(*stash);
	*stash = temp;
	return (copy);
}

size_t	ft_strlen_gnl(char *c, int type)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	if (type == 0)
		while (c[i])
			i++;
	if (type == 1)
	{
		while (c[i] && c[i] != '\n')
			i++;
		if (c[i] == '\n')
			i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*s3;

	len1 = ft_strlen_gnl(s1, 0);
	len2 = ft_strlen_gnl(s2, 0);
	i = 0;
	j = 0;
	s3 = malloc(len1 + len2 + 1);
	if (!s3)
		return (NULL);
	while (i < len1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < len2)
		s3[i++] = s2[j++];
	s3[i] = 0;
	return (s3);
}
