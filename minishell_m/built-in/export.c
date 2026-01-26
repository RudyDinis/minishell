/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:28:59 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/26 18:21:16 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_and_replace(t_env **env, char *arg)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
			i++;
		else
		{
			res[j] = arg[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	printf ("%s\n", res);
	add_env(env, res);
	free(res);
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
		find_and_replace(env, arg);
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

