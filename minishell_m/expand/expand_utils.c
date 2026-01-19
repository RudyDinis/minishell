/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:32:36 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/19 13:38:39 by rdinis           ###   ########.fr       */
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

void	expand_one_var2_doc(char *val, char *env,
	t_expand_vars_vars *vars, int quoted)
{
	char	**split;
	int		j;
	char	*v;

	if (val != NULL)
		v = val;
	else
		v = env;
	if (!quoted)
	{
		split = ft_split(v, " \t");
		if (!split)
			return ;
		j = 0;
		while (split[j] != NULL)
		{
			vars->res = ft_strjoin(vars->res, split[j]);
			if (split[j + 1] != NULL)
				vars->res = ft_strjoin_free(vars->res, " ");
			j++;
		}
		free_tab(split);
	}
	else
		vars->res = ft_strjoin(vars->res, v);
}


char	*expand_one_var_doc(t_expand_vars_vars *vars,
	t_minishell *data, int quoted)
{
	char	*name;
	char	*val;
	char	*env;
	int		start;

	(vars->i)++;
	start = vars->i;
	if (vars->s[vars->i] == '?')
		return (vars->res = ft_strjoin(vars->res,
				ft_itoa(data->last_cmd_return_value)), vars->i++, vars->res);
	while (ft_isalnum(vars->s[vars->i]) || vars->s[vars->i] == '_')
		vars->i++;
	name = ft_substr(vars->s, start, vars->i - start);
	val = get_var_value(name, data);
	env = get_env_value(name, data);
	if (val || env)
		expand_one_var2_doc(val, env, vars, quoted);
	free(name);
	return (vars->res);
}
