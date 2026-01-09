#include "../minishell.h"

int is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

void if_space(t_repere *repere)
{
	repere->in_word = 0;
	repere->in_pipe = 0;
	repere->in_redir_in = 0;
	repere->in_redir_out = 0;
}

void if_s_quotes(t_repere *repere)
{
	if (!repere->in_d_quote)
	{
		if (repere->in_s_quote)
			repere->in_s_quote = 0;
		else
			repere->in_s_quote = 1;
	}
}

void if_d_quotes(t_repere *repere)
{
	if (!repere->in_s_quote)
	{
		if (repere->in_d_quote)
			repere->in_d_quote = 0;
		else
			repere->in_d_quote = 1;
	}
}

int check_quotes_error(int token, t_repere repere)
{
	if (repere.in_s_quote || repere.in_d_quote)
		printf("incorrect number of quotes"), exit(1); // TODO Faire un truc propre ici;
	else
		return token;
}
