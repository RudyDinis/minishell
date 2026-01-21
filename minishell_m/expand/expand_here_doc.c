/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:31:01 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 12:09:42 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_squote_doc(char *s, int *i, char *res, char *param)
{
	int		start;
	char	*tmp;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (ft_strcmp(param, "HERE_DOC") == 0)
	{
		tmp = ft_substr(s, start - 1, *i + 1);
		res = ft_strjoin_free(res, tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_substr(s, start, *i - start);
		res = ft_strjoin_free(res, tmp);
		free(tmp);
	}
	if (s[*i] == '\'')
		(*i)++;
	return (res);
}

char	*handle_dquote_doc(t_expand_vars_vars *vars,
	t_minishell *data, char *param)
{
	vars->i++;

	if (!ft_strcmp(param, "HERE_DOC"))
		vars->res = char_join(vars->res, '"');

	while (vars->s[vars->i] && vars->s[vars->i] != '"')
	{
		if (vars->s[vars->i] == '$'
			&& (isalnum(vars->s[vars->i + 1]) || vars->s[vars->i + 1] == '?'))
			vars->res = expand_one_var_doc(vars, data, 1);
		else
			vars->res = char_join(vars->res, vars->s[vars->i++]);
	}
	if (vars->s[vars->i] == '"')
		vars->i++;

	if (!ft_strcmp(param, "HERE_DOC"))
		vars->res = char_join(vars->res, '"');

	return (vars->res);
}


char	*handle_squote_doc_doc(t_expand_vars_vars *vars,
	t_minishell *data, char *param)
{
	vars->i++;
	vars->res = char_join(vars->res, '\'');
	while (vars->s[vars->i] && vars->s[vars->i] != '\'')
	{
		if (vars->s[vars->i] == '$' && (vars->s[vars->i + 1]
				&& (isalnum(vars->s[vars->i + 1])
					|| vars->s[vars->i + 1] == '?')))
			vars->res = expand_one_var_doc(vars, data, 1);
		else
			vars->res = char_join(vars->res, vars->s[vars->i++]);
	}
	if (vars->s[vars->i] == '\'')
		vars->i++;
	vars->res = char_join(vars->res, '\'');
	return (vars->res);
}

void	expand_vars2_doc(t_minishell *data,
	t_expand_vars_vars *vars, char *param)
{
	if (vars->s[vars->i] == '\'' && !ft_strcmp(param, "HERE_DOC"))
		handle_squote_doc_doc(vars, data, param);
	else if (vars->s[vars->i] == '\'')
		vars->res = handle_squote_doc(vars->s, &vars->i, vars->res, param);
	else if (vars->s[vars->i] == '"')
		vars->res = handle_dquote_doc(vars, data, param);
	else if (vars->s[vars->i] == '$'
		&& (isalnum(vars->s[vars->i + 1]) || vars->s[vars->i + 1] == '?'))
	{
		if (!ft_strcmp(param, "FILE"))
			vars->res = expand_one_var_doc(vars, data, 1);
		else
			vars->res = expand_one_var_doc(vars, data, 0);
	}
	else
		vars->res = char_join(vars->res, vars->s[vars->i++]);
}


char	**expand_vars_doc(char *s, t_minishell *data, char *param)
{
	t_expand_vars_vars	vars;
	char				**res_array;
	char				*final;

	vars.i = 0;
	vars.res = ft_strdup("");
	vars.s = s;
	while (s[vars.i])
		expand_vars2_doc(data, &vars, param);

	final = ft_strdup(vars.res);
	free(vars.res);
	if (!ft_strcmp(param, "FILE")
		|| !ft_strcmp(param, "HERE_DOC"))
	{
		res_array = malloc(sizeof(char *) * 2);
		res_array[0] = final;
		res_array[1] = NULL;
		return (res_array);
	}
	return (res_array = malloc(sizeof(char *) * 2),
		res_array[0] = final,
		res_array[1] = NULL,
		res_array);
}
