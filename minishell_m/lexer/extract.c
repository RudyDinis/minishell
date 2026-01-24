/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:39:16 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	extract_word_check_quotes(char buf, t_repere *repere)
{
	if (buf == '\'' && !repere->in_d_quote)
	{
		if ((buf == '\'') && repere->in_s_quote)
			repere->in_s_quote = 0;
		else
			repere->in_s_quote = 1;
	}
	if (buf == '\"' && !repere->in_s_quote)
	{
		if ((buf == '\"') && repere->in_d_quote)
			repere->in_d_quote = 0;
		else
			repere->in_d_quote = 1;
	}
}

int	extract_size(char *buf)
{
	int			i;
	t_repere	repere;

	i = 0;
	repere = init_repere();
	while (buf[i])
	{
		extract_word_check_quotes(buf[i], &repere);
		if ((!repere.in_s_quote && !repere.in_d_quote) && (v(buf[i])
				|| buf[i] == '|' || buf[i] == '<' || buf[i] == '>'))
			break ;
		i++;
	}
	return (i);
}

char	*extract_word(char *buf)
{
	int		i;
	int		size;
	char	*line;

	size = extract_size(buf);
	i = 0;
	if (!buf)
		return (NULL);
	line = malloc(size + 1);
	if (!line)
		return (NULL);
	while (buf[i] && i < size)
	{
		line[i] = buf[i];
		i++;
	}
	return (line[i] = 0, line);
}
