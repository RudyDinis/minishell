/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:33:38 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/25 17:23:26 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			vars->res = ft_strjoin_free(vars->res, split[j]);
			if (split[j + 1] != NULL)
				vars->res = ft_strjoin_free(vars->res, " ");
			j++;
		}
		free_everything((void **)split);
	}
	else
		vars->res = ft_strjoin_free(vars->res, v);
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
	while (ft_isalnum(vars->s[vars->i]) || vars->s[vars->i] == '_'
		|| (vars->s[vars->i] == '?' && vars->i == start))
	{
		vars->i++;
		if (vars->s[vars->i - 1] == '?')
			break ;
	}
	name = ft_substr(vars->s, start, vars->i - start);
	val = get_var_value(name, data);
	env = get_env_value(name, data);
	if (val || env)
		expand_one_var2_doc(val, env, vars, quoted);
	free(name);
	return (vars->res);
}
