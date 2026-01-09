#include "../minishell.h"

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

int assign_type_special_edition(char *c, t_token *token, t_repere *repere)
{
	if (c[0] == '|' && !repere->in_pipe && !repere->in_d_quote && !repere->in_s_quote)
		return token->line = "|", increment_repere(repere, "IN_PIPE"),
					token->type = PIPE, 1;
	if (c[0] == '>' && !repere->in_redir_out && !repere->in_d_quote && !repere->in_s_quote)
	{
		increment_repere(repere, "IN_REDIR_OUT");
		if (c[1] == '>')
			token->type = APPEND, token->line = ">>";
		else
			token->type = REDIR_OUT, token->line = ">";
		return 1;
	}
	if (c[0] == '<' && !repere->in_redir_in && !repere->in_d_quote && !repere->in_s_quote)
	{
		increment_repere(repere, "IN_REDIR_IN");
		if (c[1] == '<')
			token->type = HERE_DOC, token->line = "<<";
		else
			token->type = REDIR_IN, token->line = "<";
		return 1;
	}
	return 0;
}

int assign_type(char *c, t_token *token, t_repere *repere)
{
	if (c[0] == '\'' && !repere->in_d_quote)
	{
		if (repere->in_s_quote)
			repere->in_s_quote = 0;
		else
		{
			repere->in_s_quote = 1;
			if (!repere->in_d_quote)
				token->s_quotes_prio = 1;
		}
	}
	if (c[0] == '\"' && !repere->in_s_quote)
	{
		if (repere->in_d_quote)
			repere->in_d_quote = 0;
		else
			repere->in_d_quote = 1;
	}
	if (c[0] != '|' && c[0] != '>' && c[0] != '<' && !is_blank(c[0]) && !repere->in_word)
		return (increment_repere(repere, "IN_WORD"), token->type = STR,
			token->line = extract_word(&c[0]), 1);
	if (is_blank(c[0]) && !repere->in_d_quote && !repere->in_s_quote)
		increment_repere(repere, "RESET");
	return (assign_type_special_edition(c, token, repere));
}

void find_type(char *buf, t_token *token)
{
	int i;
	int j;
	t_repere repere;

	repere = init_repere();
	i = 0;
	while (buf[i])
	{
		if (assign_type(&buf[i], token, &repere))
			token = token->next;
		i++;
	}
}
