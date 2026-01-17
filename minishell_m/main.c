#include "minishell.h"

int is_valid_buf(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (!is_blank(buf[i++]))
			return 1;
	}
	return 0;
}

int main(void)
{
	char *buf;
	t_token *token;

	while (1)
	{
		buf = readline("$>");
		if (*buf && is_valid_buf(buf))
		{
			token = create_list(buf);
			check_formatting(token);
			free_ms(NULL, token->cmd, -5);
		}
		free(buf);
	}

	// buf = "./here_doc.o >> cc";
	// token = create_list(buf);
	// check_formatting(token);
	// free_ms(NULL, token->cmd, -5);
	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	// TODO ISATTY
	// TODO AJOUTER L'ENVP POUR LES CMDS
	return 0;
}
