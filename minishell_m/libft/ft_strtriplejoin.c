/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtriplejoin                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:55:40 by bbouarab          #+#    #+#             */
/*   Updated: 2026/01/12 10:55:03 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtriplejoin(char const *s1, char const *s2, char const *s3)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*s4;

	if (!s1 || !s2 || !s3)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	s4 = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!s4)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		s4[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
		s4[i++] = s2[j++];
	while (k < ft_strlen(s3))
		s4[i++] = s3[k++];
	s4[i] = 0;
	return (s4);
}
