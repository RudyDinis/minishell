/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 14:22:46 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/12 14:39:02 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char **argv, t_minishell *data)
{
	int	res;

	res = chdir(argv[1]);
	if (res == 0)
		data->pwd = getcwd(NULL, 0);
	else
		printf("Cannot open this directory\n");
}
