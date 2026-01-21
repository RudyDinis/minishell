/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:49:27 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 15:55:39 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_squote(t_expand_vars_vars	*vars, char *param)
{
	int		start;
	char	*tmp;

	vars->i++;
	start = vars->i;
	while (vars->s[vars->i] && vars->s[vars->i] != '\'')
		vars->i++;
	if (ft_strcmp(param, "HERE_DOC") == 0)
	{
		tmp = ft_substr(vars->s, start - 1, vars->i + 1);
		vars->res = ft_strjoin_free(vars->res, tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_substr(vars->s, start, vars->i - start);
		vars->res = ft_strjoin_free(vars->res, tmp);
		free(tmp);
	}
	if (vars->s[vars->i] == '\'')
		vars->i++;
	return (vars->res);
}

char	*handle_dquote(t_expand_vars_vars *vars, t_minishell *data, char *param)
{
	vars->i++;

	if (!ft_strcmp(param, "HERE_DOC"))
		vars->res = char_join(vars->res, '"');

	while (vars->s[vars->i] && vars->s[vars->i] != '"')
	{
		if (vars->s[vars->i] == '$'
			&& (isalnum(vars->s[vars->i + 1]) || vars->s[vars->i + 1] == '?'))
			vars->res = expand_one_var(vars, data, 1);
		else
			vars->res = char_join(vars->res, vars->s[vars->i++]);
	}
	if (vars->s[vars->i] == '"')
		vars->i++;

	if (!ft_strcmp(param, "HERE_DOC"))
		vars->res = char_join(vars->res, '"');

	return (vars->res);
}

void	expand_vars2(t_minishell *data, t_expand_vars_vars *vars, char *param)
{
	if (vars->s[vars->i] == '\'')
		vars->res = handle_squote(vars, param);
	else if (vars->s[vars->i] == '"')
		vars->res = handle_dquote(vars, data, param);
	else if (vars->s[vars->i] == '$'
		&& (isalnum(vars->s[vars->i + 1]) || vars->s[vars->i + 1] == '?'))
		vars->res = expand_one_var(vars, data, 0);
	else
	{
		if (vars->s[vars->i] == ' ')
		{
			vars->res = char_join(vars->res, '\a');
			vars->i++;
		}
		else
			vars->res = char_join(vars->res, vars->s[vars->i++]);
	}
}

char	**expand_vars_jsp(char *s, t_minishell *data, char *param)
{
	t_expand_vars_vars	vars;
	char				*final;
	char				**ret;

	if (!s)
		return (NULL);
	vars.i = 0;
	vars.res = ft_strdup("");
	vars.s = s;
	vars.a = -1;
	while (s[vars.i])
		expand_vars2(data, &vars, param);
	final = ft_strdup(vars.res);
	ret = ft_split(final, "\a");
	free(final);
	free(vars.res);
	return (ret);
}
