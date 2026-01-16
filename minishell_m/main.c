#include "minishell.h"

int main(void)
{
	char *buf;
	t_token *token;

	while (1)
	{
		buf = readline("$>");
		token = create_list(buf);
		check_formatting(token);
		free_ms(NULL, token->cmd, -5);
		free(buf);
	}
	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	return 0;
}
