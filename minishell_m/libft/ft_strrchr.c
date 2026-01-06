/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:54:48 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:55:33 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	size_t	i;

	i = 0;
	while (string[i])
		i++;
	if (string[i] == (char)searchedChar)
		return ((char *)&string[i]);
	while (i > 0)
	{
		i--;
		if (string[i] == ((char)searchedChar))
			return ((char *)&string[i]);
	}
	return (NULL);
}
