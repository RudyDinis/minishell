#include "../minishell.h"

void if_word(t_repere *repere, int *token)
{
	(*token)++;
	repere->in_word = 1;
	repere->in_pipe = 0;
	repere->in_redir_in = 0;
	repere->in_redir_out = 0;
}

void if_pipe(char *buf, t_repere *repere, int *token)
{
	if (buf[1] && buf[1] == '|')
		return (ft_printf_error("|| operator not supported\n"), exit(1));
	(*token)++;
	repere->in_word = 0;
	repere->in_pipe = 1;
	repere->in_redir_in = 0;
	repere->in_redir_out = 0;
}

void if_redir_in(char *buf, t_repere *repere, int *token)
{
	repere->in_word = 0;
	repere->in_pipe = 0;
	repere->in_redir_in = 1;
	repere->in_redir_out = 0;
	if (buf[1] && buf[1] == '<')
	{
		if (buf[2] && buf[2] == '<')
			return (ft_printf_error("syntax error near unexpected token \'<\'\n"),
 				exit(1));
		(*token)++;
	}
	else
		(*token)++;
}

void if_redir_out(char *buf, t_repere *repere, int *token)
{
	repere->in_word = 0;
	repere->in_pipe = 0;
	repere->in_redir_in = 0;
	repere->in_redir_out = 1;
	if (buf[1] && buf[1] == '>')
	{
		if (buf[2] && buf[2] == '>')
			return (ft_printf_error("syntax error near unexpected token \'>\'\n"),
 				exit(1));
		(*token)++;
	}
	else
		(*token)++;
}

int find_number_of_token(char *buf)
{
	int (i) = 0;
	int token;
	t_repere repere;
	token = 0;
	repere = init_repere();
	while (buf[i])
	{
		if (buf[i] == '\'')
			if_s_quotes(&repere);
		if (buf[i] == '\"')
			if_d_quotes(&repere);
		if (buf[i] != '|' && buf[i] != '>' && buf[i] != '<' && !is_blank(buf[i]) && !repere.in_word)
			if_word(&repere, &token);
		if (is_blank(buf[i]) && !repere.in_d_quote && !repere.in_s_quote)
			if_space(&repere);
		if (buf[i] == '|' && !repere.in_pipe && !repere.in_s_quote && !repere.in_d_quote)
			if_pipe(&buf[i], &repere, &token);
		if (buf[i] == '>' && !repere.in_redir_out && !repere.in_s_quote && !repere.in_d_quote)
			if_redir_out(&buf[i], &repere, &token);
		if (buf[i] == '<' && !repere.in_redir_in && !repere.in_s_quote && !repere.in_d_quote)
			if_redir_in(&buf[i], &repere, &token);
		i++;
	}
	return (check_quotes_error(token, repere));
}
