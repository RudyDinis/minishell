/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:46:06 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/12 16:44:59 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *name, char *value, t_minishell *data)
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

char	*get_var_value(char *name, char *value, t_minishell *data)
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

int	get_force(char *value)
{
	if (value[0] == '\'')
		return (1);
	else if (value[0] == '\"')
		return (2);
	else
		return (0);
}

char	*get_var_name(char *value, int i)
{
	char	*res;
	int		y;
	int		j;

	j = 0;
	y = i;
	while (ft_isalnum(value[y]))
		y++;
	res = malloc(sizeof(char) * y);
	while (i < y)
	{
		res[j++] = value[i];
		i++;
	}
	return (res);
}

int	get_size_2(char *value)
{
	int	end;
	int	start;
	int	i;

	start = 1;
	end = ft_strlen(value) - 1;

	i = start;
	while (i < end)
	{
		if (value[i] == '$')
			get_var_name(value, i + 1);
		else
			printf(" ");
		i++;
	}
}

char	*check_and_replace(char *value, t_minishell *data)
{
	char	*res;
	int		force;

	res = NULL;
	//printf("%s\n", value);
	force = get_force(value);
	get_size_2(value);
	return (res);
}
