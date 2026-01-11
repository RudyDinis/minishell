#include "../minishell.h"

t_env *new_node(char *key, char *value)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return NULL;
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

void print_env(t_env *env)
{
    t_env *tmp = env;

    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void add_env(t_env **env, char *line)
{
	char *eq ;
	char *key;
	char *value;

	eq = ft_strchr(line, '=');
	if (!eq)
		return;
	key = ft_substr(line, 0, eq - line);
	value = ft_strdup(eq + 1);
	t_env *node = new_node(key, value);
	if (!*env)
	{
		*env = node;
		return;
	}
	t_env *tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}


void export(char **str, t_env *env)
{
	if (!str[1])
	{
        print_env(env);
        return;
    }
}