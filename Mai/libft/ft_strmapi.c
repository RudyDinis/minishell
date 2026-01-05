/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:49:26 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:49:50 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new;

	if (!s || !f)
		return (NULL);
	i = 0;
	new = malloc(ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	new[ft_strlen(s)] = 0;
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	return (new);
}
