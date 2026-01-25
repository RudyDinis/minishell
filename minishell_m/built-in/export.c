/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:28:59 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 13:44:41 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *new_node(char *key, char *value)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

int env_exist(t_env *tmp, char *key, char *value)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void add_env(t_env **env, char *line)
{
	char *eq;
	char *key;
	char *value;
	t_env *node;
	t_env *tmp;

	eq = ft_strchr(line, '=');
	if (!eq)
		return;
	key = ft_substr(line, 0, eq - line);
	value = ft_strdup(eq + 1);
	tmp = *env;
	if (env_exist(tmp, key, value))
		return (free(key), free(value));
	node = new_node(key, value);
	if (!*env)
	{
		*env = node;
		return;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	export2(char *arg, t_env **env)
{
	char	*eq;
	char	*key;
	char	*res;

	eq = ft_strchr(arg, '=');
	if (eq)
		key = ft_substr(arg, 0, eq - arg);
	else
		key = ft_strdup(arg);
	if (!is_valid_identifier(key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		free(key);
		return (1);
	}
	free(key);
	if (eq)
		add_env(env, arg);
	else
	{
		res = ft_strjoin(arg, "=");
		add_env(env, res);
		free(res);
	}
	return (0);
}


int	export(char **argv, t_env *env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!argv[1])
		return (print_env(env), 0);
	while (argv[i])
	{
		if (export2(argv[i], &env))
			status = 1;
		i++;
	}
	return (status);
}

