#include "minishell.h"

int main(void)
{
	char *buf;
	t_token *lst;
	t_minishell *minishell;
	int i = 0;
	minishell = malloc(sizeof(t_minishell));
	minishell->last_cmd_return_value = 0;
	minishell->pwd = NULL;
	minishell->env = malloc(sizeof(t_env));
	minishell->env->key = NULL;
	minishell->env->next = NULL;
	minishell->env->value = NULL;
	minishell->var = malloc(sizeof(t_var));
	minishell->var->key = "abc";
	minishell->var->next = NULL;
	minishell->var->value = "salut      ça      va";
	minishell->last_cmd_return_value = 0;
	while (1)
	{
		buf = readline("$>");
		i = 0;
		lst = create_list(buf);
		check_formatting(lst);
	}
	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	return 0;
}
