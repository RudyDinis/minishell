/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:08:05 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/12 11:09:01 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_everything_int(int **vector)
{
	int	i;

	i = sizeof(vector) / **vector;
	while (vector[i])
		free(vector[i++]);
	if (vector)
		free(vector);
}
