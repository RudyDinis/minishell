#include "../minishell.h"

t_var	*new_var_node(char *key, char *value)
{
	t_var *node = malloc(sizeof(t_var));
	if (!node)
		return NULL;

	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return node;
}


void	add_var(t_var **var, char *key, char *value)
{
	t_var	*tmp;

	tmp = *var;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return;
		}
		tmp = tmp->next;
	}
	while (*var)
		*var = (*var)->next;
	*var = ft_calloc(1, sizeof(t_var));
	(*var)->key = ft_strdup(key);
	(*var)->value = ft_strdup(value);
}

char	*get_env_value(char *name, t_minishell *data)
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

char	*get_var_value(char *name, t_minishell *data)
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

void	expand_one_var2(char *val, char *env, char **res, int quoted)
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
			if (j == 0)
				*res = ft_strjoin(*res, split[j]);
			else
			{
				*res = ft_strjoin(*res, "\a");
				*res = ft_strjoin(*res, split[j]);
			}
			j++;
		}
		//free_tab(split);
	}
	else
		*res = ft_strjoin(*res, v);
}


char *expand_one_var(char *s, int *i, char *res, t_minishell *data, int quoted)
{
	char *name;
	char *val;
	char *env;
	int start;

	(*i)++;
	start = *i;
	if (s[*i] == '?')
		return (res = ft_strjoin(res, ft_itoa(data->last_cmd_return_value)), (*i)++, res);
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	name = ft_substr(s, start, *i - start);
	val = get_var_value(name, data);
	env = get_env_value(name, data);
	if (val || env)
		expand_one_var2(val, env, &res, quoted);
	free(name);
	return (res);
}
