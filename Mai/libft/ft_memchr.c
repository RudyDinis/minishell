/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:33:26 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 09:04:15 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t	i;

	i = 0;
	while (i != size)
		if (((unsigned char *)memoryBlock)[i++] ==
				((unsigned char)searchedChar))
			return (&((unsigned char *)memoryBlock)[i - 1]);
	return (NULL);
}
