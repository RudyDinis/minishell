/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:32:04 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 15:41:34 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*char_join(char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	return (ft_strjoin_free(s, tmp));
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	expand_one_var3(int *j, char **split, t_expand_vars_vars *vars)
{
	if ((*j) == 0)
		vars->res = ft_strjoin_free(vars->res, split[*j]);
	else
	{
		vars->res = ft_strjoin_free(vars->res, "\a");
		vars->res = ft_strjoin_free(vars->res, split[*j]);
	}
	(*j)++;
}

void	expand_one_var2(char *val, char *env,
		t_expand_vars_vars *vars, int quoted)
{
	char		**split;
	int			j;
	char		*v;

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
			expand_one_var3(&j, split, vars);
		}
		free_tab(split);
	}
	else
		vars->res = ft_strjoin_free(vars->res, v);
}

char	*expand_one_var(t_expand_vars_vars *vars, t_minishell *data, int quoted)
{
	char	*name;
	char	*val;
	char	*env;
	int		start;

	if (vars->s[vars->i - 1] && vars->s[vars->i - 1] == ' ')
		vars->res = char_join(vars->res, '\a');
	vars->i++;
	start = vars->i;
	while (ft_isalnum(vars->s[vars->i]) || vars->s[vars->i] == '_'
		|| vars->s[vars->i] == '?')
		vars->i++;
	name = ft_substr(vars->s, start, vars->i - start);
	val = get_var_value(name, data);
	env = get_env_value(name, data);
	if (val || env)
		expand_one_var2(val, env, vars, quoted);
	free(name);
	if (vars->s[vars->i] && vars->s[vars->i] == ' ')
		vars->res = char_join(vars->res, '\a');
	return (vars->res);
}

char	**expand_vars(char *s, t_minishell *data, char *param)
{
	if (!strcmp(param, "HERE_DOC") || !strcmp(param, "FILE"))
		return (expand_vars_doc(s, data, param));
	else
		return (expand_vars_jsp(s, data, param));
}
