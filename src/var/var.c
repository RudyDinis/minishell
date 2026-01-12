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

char *char_join(char *s, char c)
{
	char tmp[2] = {c, 0};
	return (ft_strjoin_free(s, tmp));
}

char *expand_one_var(char *s, int *i, char *res, t_minishell *data)
{
	char *name;
	char *val;
	char *env;
	int start;

	(*i)++;
	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;

	name = ft_substr(s, start, *i - start);
	val = get_var_value(name, NULL, data);
	env = get_env_value(name, NULL, data);

	if (val)
		res = ft_strjoin_free(res, val);
	else if (env)
		res = ft_strjoin_free(res, env);

	free(name);
	return (res);
}

char	*handle_squote(char *s, int *i, char *res)
{
	int	start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	res = ft_strjoin_free(res, ft_substr(s, start, *i - start));
	if (s[*i] == '\'')
		(*i)++;
	return (res);
}


char	*handle_dquote(char *s, int *i, char *res, t_minishell *data)
{
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
			res = expand_one_var(s, i, res, data);
		else
			res = char_join(res, s[(*i)++]);
	}
	if (s[*i] == '"')
		(*i)++;
	return (res);
}


char	*expand_vars(char *s, t_minishell *data)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\'')
			res = handle_squote(s, &i, res);
		else if (s[i] == '"')
			res = handle_dquote(s, &i, res, data);
		else if (s[i] == '$')
			res = expand_one_var(s, &i, res, data);
		else
			res = char_join(res, s[i++]);
	}
	return (res);
}
