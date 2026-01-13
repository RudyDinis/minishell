#include "minishell.h"

int main(void)
{
	char *buf;
	t_token *lst;
	t_minishell *minishell;
	minishell = malloc(sizeof(minishell));
	minishell->last_cmd_return_value = 0;
	minishell->pwd = NULL;
	minishell->env = malloc(sizeof(t_env));
	minishell->env->key = NULL;
	minishell->env->next = NULL;
	minishell->env->value = NULL;
	minishell->var = malloc(sizeof(t_var));
	minishell->var->key = NULL;
	minishell->var->next = NULL;
	minishell->var->value = NULL;
	while (1)
	{
		buf = readline("$>");
		char **result = expand_vars(buf, minishell);
		// buf = "< tesuto echo test > test | echo salut";
		printf("%s\n", result[0]);
		// lst = create_list(buf);
		// heck_formatting(lst);
	}
	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	return 0;
}
