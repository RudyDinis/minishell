/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:52:22 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:54:33 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1)
		return (NULL);
	if (ft_strlen(s2) == 0)
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		while (s1[i + j] && s2[j]
			&& (s1[i + j] == s2[j])
			&& (i + j) < len)
			j++;
		if (s2[j] == '\0')
			return (&((char *)s1)[i]);
		j = 0;
		i++;
	}
	return (NULL);
}
