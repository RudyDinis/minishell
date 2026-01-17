/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:28:59 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/14 16:22:52 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("export %s", tmp->key);
		if (ft_strlen(tmp->value))
			printf("=\"%s\"\n", tmp->value);
		else
			printf("\n");
		tmp = tmp->next;
	}
}

int		env_exist(t_env *tmp, char *key, char *value)
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

void	add_env(t_env **env, char *line)
{
	char	*eq ;
	char	*key;
	char	*value;
	t_env	*node;
	t_env	*tmp;


	eq = ft_strchr(line, '=');
	if (!eq)
		return ;
	key = ft_substr(line, 0, eq - line);
	value = ft_strdup(eq + 1);
	tmp = *env;
	if (env_exist(tmp, key, value))
		return (free(key), free(value));
	node = new_node(key, value);
	if (!*env)
	{
		*env = node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	export(char **argv, t_env *env)
{
	int		i;
	char	*res;

	i = 1;
	if (!argv[1])
		return (print_env(env), 0);
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			add_env(&env, argv[i]);
		else
		{
			res = ft_strjoin(argv[i], "=");
			add_env(&env, res);
			free(res);
		}
		i++;
	}
}

