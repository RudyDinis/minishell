/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:47:30 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 09:02:16 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	if (!dst)
		return ((size_t) NULL);
	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	j = dstlen;
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	while (src[i] && (j + 1) < dstsize)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = 0;
	return (dstlen + srclen);
}
