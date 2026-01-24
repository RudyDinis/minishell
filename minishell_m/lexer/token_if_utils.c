/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_if_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:38:06 by bbouarab         ###   ########.fr       */
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
