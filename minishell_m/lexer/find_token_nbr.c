/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 20:00:07 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_word(t_repere *repere, int *token)
{
	(*token)++;
	repere->in_word = 1;
	repere->in_pipe = 0;
	repere->in_redir_in = 0;
	repere->in_redir_out = 0;
}

void	if_pipe(char *buf, t_repere *repere, int *token)
{
	if (buf[1] && buf[1] == '|')
		return (ft_printf_error("|| operator not supported\n"),
			repere->error = 1, (void)0);
	(*token)++;
	repere->in_word = 0;
	repere->in_pipe = 1;
	repere->in_redir_in = 0;
	repere->in_redir_out = 0;
}

void	if_redir_in(char *buf, t_repere *repere, int *token)
{
	repere->in_word = 0;
	repere->in_pipe = 0;
	repere->in_redir_in = 1;
	repere->in_redir_out = 0;
	if (buf[1] && buf[1] == '<')
	{
		if (buf[2] && buf[2] == '<')
			return (ft_printf_error
				("syntax error near unexpected token `newline'\n"),
				repere->error = 1, (void)0);
		(*token)++;
	}
	else
		(*token)++;
}

void	if_redir_out(char *buf, t_repere *repere, int *token)
{
	repere->in_word = 0;
	repere->in_pipe = 0;
	repere->in_redir_in = 0;
	repere->in_redir_out = 1;
	if (buf[1] && buf[1] == '>')
	{
		if (buf[2] && buf[2] == '>')
			return (ft_printf_error
				("syntax error near unexpected token `newline'\n"),
				repere->error = 1, (void)0);
		(*token)++;
	}
	else
		(*token)++;
}

int	if_and_operator(char *buf, t_repere *repere)
{
	if (!repere->in_s_quote && !repere->in_d_quote && repere->in_word)
	{
		if (buf[0] && buf[0] == '&' && buf[1] && buf[1] == '&')
			return (ft_printf_error("&& operator not supported\n"),
				repere->error = 1, 0);
		if (buf[0] && buf[0] == '&')
			return (ft_printf_error("& operator not supported\n"),
				repere->error = 1, 0);
	}
	return (1);
}

int	find_number_of_token(char *s)
{
	int (i) = 0;
	int (token) = 0;
	t_repere (r) = init_repere();
	while (s[i])
	{
		if (s[i] == '\'')
			if_s_quotes(&r);
		if (s[i] == '\"')
			if_d_quotes(&r);
		if (s[i] != '|' && s[i] != '>' && s[i] != '<' && !v(s[i]) && !r.in_word)
			if_word(&r, &token);
		if (v(s[i]) && !r.in_d_quote && !r.in_s_quote)
			if_space(&r);
		if (s[i] == '|' && !r.in_pipe && !r.in_s_quote && !r.in_d_quote)
			if_pipe(&s[i], &r, &token);
		if (s[i] == '>' && !r.in_redir_out && !r.in_s_quote && !r.in_d_quote)
			if_redir_out(&s[i], &r, &token);
		if (s[i] == '<' && !r.in_redir_in && !r.in_s_quote && !r.in_d_quote)
			if_redir_in(&s[i], &r, &token);
		if (!if_and_operator(&s[i], &r) && r.error)
			return (0);
		i++;
	}
	return (check_quotes_error(token, r));
}
