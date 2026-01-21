/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:32:36 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 13:42:42 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*new_var_node(char *key, char *value)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}


void	add_var(t_var **var, char *key, char *value)
{
	t_var	*tmp;

	tmp = *var;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	while (*var)
		*var = (*var)->next;
	*var = ft_calloc(1, sizeof(t_var));
	if (!(*var))
		return ;
	(*var)->key = ft_strdup(key);
	(*var)->value = ft_strdup(value);
}

char	*get_env_value(char *name, t_minishell *data)
{
	t_env	*tmp_env;

	tmp_env = data->env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, name) == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
}

char	*get_var_value(char *name, t_minishell *data)
{
	t_var	*tmp_var;

	tmp_var = data->var;
	while (tmp_var)
	{
		if (ft_strcmp(tmp_var->key, name) == 0)
			return (tmp_var->value);
		tmp_var = tmp_var->next;
	}
}
