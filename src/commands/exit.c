/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:27:10 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/14 18:07:53 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_shell(t_minishell *data)
{
	t_env	*tmp;
	t_var	*tmp_var;

	while (data->env)
	{
		tmp = data->env->next;
		free(data->env->key);
		free(data->env->value);
		free(data->env);
		data->env = tmp;
	}
	while (data->var)
	{
		tmp_var = data->var->next;
		free(data->var->key);
		free(data->var->value);
		free(data->var);
		data->var = tmp_var;
	}
	if (data->pwd)
		free(data->pwd);
	free(data);
	exit(1);
}
