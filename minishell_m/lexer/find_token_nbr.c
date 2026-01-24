/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/25 00:02:01 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (!if_and_operator(&s[i], &r) || r.error)
			return (0);
		i++;
	}
	printf("VALEUR DE TOKEN = %d\n", token);
	return (check_quotes_error(token, r));
}
