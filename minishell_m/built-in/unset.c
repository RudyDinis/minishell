/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 23:08:47 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_var(t_var **var, char *key)
{
	t_var	*tmp;
	t_var	*prev;

	tmp = *var;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*var = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	if (!key)
		return ;
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset(t_minishell *data, char *key)
{
	unset_var(&data->var, key);
	unset_env(&data->env, key);
}
