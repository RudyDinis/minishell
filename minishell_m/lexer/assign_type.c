#include "minishell.h"

t_repere init_repere(void)
{
	t_repere repere;

	repere.in_pipe = 0;
	repere.in_redir_in = 0;
	repere.in_redir_out = 0;
	repere.in_word = 0;
	return (repere);
}

void increment_repere_2(t_repere *repere, char *str)
{
	if (!ft_findstr(str, "IN_REDIR_IN"))
	{
		repere->in_word = 0;
		repere->in_pipe = 0;
		repere->in_redir_in = 1;
		repere->in_redir_out = 0;
	}
	if (!ft_findstr(str, "IN_REDIR_OUT"))
	{
		repere->in_word = 0;
		repere->in_pipe = 0;
		repere->in_redir_in = 0;
		repere->in_redir_out = 1;
	}
	if (!ft_findstr(str, "RESET"))
	{
		repere->in_word = 0;
		repere->in_pipe = 0;
		repere->in_redir_in = 0;
		repere->in_redir_out = 0;
	}
}

void increment_repere(t_repere *repere, char *str)
{
	if (!ft_findstr(str, "IN_WORD"))
	{
		repere->in_word = 1;
		repere->in_pipe = 0;
		repere->in_redir_in = 0;
		repere->in_redir_out = 0;
	}
	if (!ft_findstr(str, "IN_PIPE"))
	{
		repere->in_word = 0;
		repere->in_pipe = 1;
		repere->in_redir_in = 0;
		repere->in_redir_out = 0;
	}
	increment_repere_2(repere, str);
}

int assign_type_redir_edition(char *c, t_token *token, t_repere *repere)
{
	if (c[0] == '>' && !repere->in_redir_out)
	{
		increment_repere(repere, "IN_REDIR_OUT");
		if (c[1] == '>')
			token->type = APPEND;
		else
			token->type = REDIR_OUT;
		return 1;
	}
	if (c[0] == '<' && !repere->in_redir_in)
	{
		increment_repere(repere, "IN_REDIR_IN");
		if (c[1] == '<')
			token->type = HERE_DOC;
		else
			token->type = REDIR_IN;
		return 1;
	}
	return 0;
}
int assign_type(char *c, t_token *token, t_repere *repere)
{
	if (c[0] != '|' && c[0] != '>' && c[0] != '<' && c[0] != ' ' && !repere->in_word)
	{
		increment_repere(repere, "IN_WORD");
		token->type = STR;
		return 1;
	}
	if (c[0] == '|' && !repere->in_pipe)
	{
		increment_repere(repere, "IN_PIPE");
		token->type = PIPE;
		return 1;
	}
	return (assign_type_redir_edition(c, token, repere));
}
