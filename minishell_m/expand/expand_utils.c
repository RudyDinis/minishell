#include "../minishell.h"

char *char_join(char *s, char c)
{
	char tmp[2] = {c, 0};
	return (ft_strjoin(s, tmp));
}

char *expand_one_var(char *s, int *i, char *res, t_minishell *data)
{
	char *name;
	char *val;
	char *env;
	int start;

	(*i)++;
	start = *i;
	if (s[*i] == '?')
		return (res = ft_strjoin(res, ft_itoa(data->last_cmd_return_value)),
				(*i)++, res);
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;

	name = ft_substr(s, start, *i - start);
	val = get_var_value(name, NULL, data);
	env = get_env_value(name, NULL, data);

	if (val)
		res = ft_strjoin(res, val);
	else if (env)
		res = ft_strjoin(res, env);

	free(name);
	return (res);
}

char *handle_squote(char *s, int *i, char *res)
{
	int start;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	res = ft_strjoin(res, ft_substr(s, start, *i - start));
	if (s[*i] == '\'')
		(*i)++;
	return (res);
}

char *handle_dquote(char *s, int *i, char *res, t_minishell *data)
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

char **expand_vars(char *s, t_minishell *data)
{
	int 	i;
	char 	*res;
	char 	**res_array;
	int		in_quotes;

	i = 0;
	in_quotes = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\'')
			res = handle_squote(s, &i, res);
		else if (s[i] == '"')
		{
			in_quotes = 1;
			res = handle_dquote(s, &i, res, data);
		}
		else if (s[i] == '$')
			res = expand_one_var(s, &i, res, data);
		else
			res = char_join(res, s[i++]);
	}
	if (in_quotes)
		return (res_array = malloc(sizeof(char *) * 2), res_array[0] = ft_strdup(res), res_array[1] = NULL, res_array);
	else
		return ft_split(res, " \t");
}
