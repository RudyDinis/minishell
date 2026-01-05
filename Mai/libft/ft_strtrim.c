/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:55:40 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:58:47 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	is_beg;
	char	*trimmed;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	is_beg = 0;
	while (s1[is_beg] && is_set(s1[is_beg], set))
		is_beg++;
	while (len > is_beg && is_set(s1[len - 1], set))
		len--;
	trimmed = malloc(len - is_beg + 1);
	if (!trimmed)
		return (NULL);
	while (s1[is_beg] && is_beg + i < len)
	{
		trimmed[i] = s1[is_beg + i];
		i++;
	}
	trimmed[i] = 0;
	return (trimmed);
}
