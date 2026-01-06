/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:32:33 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/12 10:42:55 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findstr(char *str, char *searched)
{
	int	i;

	if (!str || !searched)
		return (1);
	i = 0;
	while (str[i] && searched[i])
	{
		if (str[i] != searched[i])
			return (1);
		i++;
	}
	if (str[i] == searched[i] || searched[i] == '\n')
		return (0);
	return (1);
}
