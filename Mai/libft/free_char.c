/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:08:05 by bbouarab          #+#    #+#             */
/*   Updated: 2025/12/12 11:09:14 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_everything(void **vector)
{
	int	i;

	i = 0;
	while (vector[i])
		free(vector[i++]);
	if (vector)
		free(vector);
}
