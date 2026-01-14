#include "../minishell.h"

char	*char_join(char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	return (ft_strjoin(s, tmp));
}

char	*handle_squote(char *s, int *i, char *res)
{
	int	start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	res = ft_strjoin(res, ft_substr(s, start, *i - start));
	if (s[*i] == '\'')
		(*i)++;
	return (res);
}

char	*handle_dquote(char *s, int *i, char *res, t_minishell *data)
{
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$' && (s[*i + 1] && isalnum(s[*i + 1])))
			res = expand_one_var(s, i, res, data);
		else
			res = char_join(res, s[(*i)++]);
	}
	if (s[*i] == '"')
		(*i)++;
	return (res);
}

void	expand_vars2(t_minishell *data, t_expand_vars_vars *vars)
{
	if (vars->s[vars->i] == '\'')
		vars->res = handle_squote(vars->s, &vars->i, vars->res);
	else if (vars->s[vars->i] == '"')
	{
		vars->in_quotes = 1;
		vars->res = handle_dquote(vars->s, &vars->i, vars->res, data);
	}
	else if (vars->s[vars->i] == '$'
		&& (vars->s[vars->i + 1] && isalnum(vars->s[vars->i + 1])))
		vars->res = expand_one_var(vars->s, &vars->i, vars->res, data);
	else
		vars->res = char_join(vars->res, vars->s[vars->i++]);
}

char	**expand_vars(char *s, t_minishell *data, char *param)
{
	t_expand_vars_vars	*vars;
	char				**res_array;

	vars = malloc(sizeof(t_expand_vars_vars));
	vars->i = 0;
	vars->in_quotes = 0;
	vars->res = ft_strdup("");
	vars->s = s;
	while (s[vars->i])
		expand_vars2(data, vars);
	if (vars->in_quotes && ft_strcmp(param, "FILE") != 0)
		return (res_array = malloc(sizeof(char *) * 2),
			res_array[0] = ft_strdup(vars->res),
			res_array[1] = NULL, res_array);
	else
		return (ft_split(vars->res, " \t"));
}
