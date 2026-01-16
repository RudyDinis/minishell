/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:28:34 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/14 14:49:42 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **argv)
{
	int i;
	int j;
	int newline;

	i = 1;
	newline = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break;
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

