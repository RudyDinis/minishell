/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:44:39 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:46:19 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int searchedChar )
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == ((char)searchedChar))
			return ((char *)&string[i]);
		i++;
	}
	if (string[i] == (char)searchedChar)
		return ((char *)&string[i]);
	return (NULL);
}
