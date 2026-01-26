/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/26 15:48:27 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_pwd(t_minishell *data, char *pwd)
{
	char	*join;

	join = ft_strjoin("PWD=", pwd);
	add_env(&data->env, join);
	free(join);
	free(pwd);
}

void	cd2(t_minishell *data, int res, char **argv)
{
	char	*pwd;

	if (res == 0)
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
			add_new_pwd(data, pwd);
		data->last_cmd_return_value = 0;
	}
	else
		return (data->last_cmd_return_value = 1, perror(argv[1]));
}

void	cd(char **argv, t_minishell *data)
{
	int	res;

	if (data->pwd_err == 1)
	{
		ft_printf_error(CDERR1 ERR2 ERR3 CDERR4);
		res = chdir("/home");
		add_new_pwd(data, ft_strdup("/home"));
		data->pwd_err = 0;
		data->last_cmd_return_value = 0;
		return ;
	}
	if (!argv[1])
		return (data->last_cmd_return_value = 1, (void) 1);
	if (argv[2])
	{
		ft_printf_error("cd: too many arguments\n");
		data->last_cmd_return_value = 2;
		return ;
	}
	res = chdir(argv[1]);
	cd2(data, res, argv);
}
