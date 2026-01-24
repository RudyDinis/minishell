/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:20:47 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_here_doc(t_cmd *cmd)
{
	int	i;
	int	j;

	j = 0;
	while (cmd)
	{
		i = 0;
		j = 0;
		if (cmd->redir->target)
		{
			malloc_redir(cmd);
			while (cmd->redir->target[i])
			{
				if (cmd->redir->redir_type[i] == HERE_DOC)
				{
					if (cmd->redir->here_doc_expand[j++] == 0)
						here_doc(cmd, cmd->redir->target[i], i);
					else
						here_doc_expand(cmd, cmd->redir->target[i], i);
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
}

char	*ignore_quotes(char *str)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			j++;
		i++;
	}
	copy = malloc((i - j) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i])
			copy[j++] = str[i++];
	}
	return (copy[j] = 0, copy);
}

int	should_expand_here_doc(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

int	get_here_doc_nbr(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == HERE_DOC)
			i++;
		token = token->next;
	}
	return (i);
}
