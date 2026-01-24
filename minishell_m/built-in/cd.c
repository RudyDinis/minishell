/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:32:51 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(char **argv, t_minishell *data)
{
	int	res;

	if (!argv[1])
	{
		data->last_cmd_return_value = 1;
		return ;
	}
	if (argv[2])
	{
		ft_printf_error("cd: too many arguments\n");
		data->last_cmd_return_value = 1;
		return ;
	}
	res = chdir(argv[1]);
	if (res == 0)
	{
		if (data->pwd)
			free(data->pwd);
		data->pwd = getcwd(NULL, 0);
		data->last_cmd_return_value = 0;
	}
	else
		return (data->last_cmd_return_value = 1, perror(argv[1]));
}
