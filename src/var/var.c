/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:46:06 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/15 13:49:16 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *char_join(char *s, char c)
{
	char tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	return (ft_strjoin_free(s, tmp));
}

char *handle_squote(char *s, int *i, char *res, char *param)
{
	int start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (ft_strcmp(param, "HERE_DOC") == 0)
		res = ft_strjoin_free(res, ft_substr(s, start - 1, *i + 1));
	else
		res = ft_strjoin_free(res, ft_substr(s, start, *i - start));
	if (s[*i] == '\'')
		(*i)++;
	return (res);
}

char *handle_dquote(t_expand_vars_vars *vars, t_minishell *data, char *param)
{
	vars->i++;
	if (ft_strcmp(param, "HERE_DOC") == 0)
		vars->res = char_join(vars->res, '"');
	while (vars->s[vars->i] && vars->s[vars->i] != '"')
	{
		if (vars->s[vars->i] == '$' && (vars->s[vars->i + 1] && (isalnum(vars->s[vars->i + 1]) || vars->s[vars->i + 1] == '?')))
			vars->res = expand_one_var(vars->s, &vars->i, vars->res, data);
		else
			vars->res = char_join(vars->res, vars->s[vars->i++]);
	}
	if (vars->s[vars->i] == '"')
		vars->i++;
	if (ft_strcmp(param, "HERE_DOC") == 0)
		vars->res = char_join(vars->res, '"');
	return (vars->res);
}

char *handle_squote_doc(t_expand_vars_vars *vars, t_minishell *data, char *param)
{
	vars->i++;
	vars->res = char_join(vars->res, '\'');
	while (vars->s[vars->i] && vars->s[vars->i] != '\'')
	{
		if (vars->s[vars->i] == '$' && (vars->s[vars->i + 1] && (isalnum(vars->s[vars->i + 1]) || vars->s[vars->i + 1] == '?')))
			vars->res = expand_one_var(vars->s, &vars->i, vars->res, data);
		else
			vars->res = char_join(vars->res, vars->s[vars->i++]);
	}
	if (vars->s[vars->i] == '\'')
		vars->i++;
	vars->res = char_join(vars->res, '\'');
	return (vars->res);
}

void expand_vars2(t_minishell *data, t_expand_vars_vars *vars, char *param)
{
	if (vars->s[vars->i] == '\'' && ft_strcmp(param, "HERE_DOC") == 0)
		handle_squote_doc(vars, data, param);
	else if (vars->s[vars->i] == '\'')
		vars->res = handle_squote(vars->s, &vars->i, vars->res, param);
	else if (vars->s[vars->i] == '"')
	{
		vars->in_quotes = 1;
		vars->res = handle_dquote(vars, data, param);
	}
	else if (vars->s[vars->i] == '$' && (vars->s[vars->i + 1] && (isalnum(vars->s[vars->i + 1]) || vars->s[vars->i + 1] == '?')))
		vars->res = expand_one_var(vars->s, &vars->i, vars->res, data);
	else
		vars->res = char_join(vars->res, vars->s[vars->i++]);
}

char **expand_vars(char *s, t_minishell *data, char *param)
{
	t_expand_vars_vars *vars;
	char **res_array;

	vars = malloc(sizeof(t_expand_vars_vars));
	vars->i = 0;
	vars->in_quotes = 0;
	vars->res = ft_strdup("");
	vars->s = s;
	while (s[vars->i])
		expand_vars2(data, vars, param);
	if (ft_strcmp(param, "FILE") == 0)
		return (res_array = malloc(sizeof(char *) * 2),
				res_array[0] = ft_strdup(vars->res),
				res_array[1] = NULL, res_array);
	if (ft_strcmp(param, "HERE_DOC") == 0)
		return (res_array = malloc(sizeof(char *) * 2),
				res_array[0] = ft_strdup(vars->res),
				res_array[1] = NULL, res_array);
	if (vars->in_quotes)
	{
		return (res_array = malloc(sizeof(char *) * 2),
				res_array[0] = ft_strdup(vars->res),
				res_array[1] = NULL, res_array);
	}
	else
	{
		return (ft_split(vars->res, " \t"));
	}
}
