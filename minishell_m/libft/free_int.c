/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:08:05 by bbouarab          #+#    #+#             */
/*   Updated: 2026/01/12 16:16:15 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_everything_int(int **vector, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
		free(vector[i++]);
	if (vector)
		free(vector);
}
