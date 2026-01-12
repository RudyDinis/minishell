#include "../minishell.h"

t_var	*new_var_node(char *key, char *value)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_var(t_var **var, char *key, char *value)
{
	char	*eq ;
	t_var	*node;
	t_var	*tmp;

	node = new_var_node(key, value);
	if (!*var)
	{
		*var = node;
		return ;
	}
	tmp = *var;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

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