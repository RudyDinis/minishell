/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:59:04 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:59:32 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
	{
		dest = malloc(1);
		if (!dest)
			return (NULL);
		return (dest[0] = 0, dest);
	}
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	i = 0;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len && s[start + i])
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
