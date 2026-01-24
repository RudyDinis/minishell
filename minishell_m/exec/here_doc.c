/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:20:57 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_here_doc_expand(t_token *token, t_cmd *cmd)
{
	int	i;
	int	here_doc_nbr;

	i = 0;
	here_doc_nbr = get_here_doc_nbr(token);
	if (!here_doc_nbr)
	{
		cmd->redir->here_doc_expand = NULL;
		return ;
	}
	cmd->redir->here_doc_expand = malloc(here_doc_nbr * sizeof(int));
	if (!cmd->redir->here_doc_expand)
		return (free_ms(cmd->token, NULL, 1));
	while (token && token->type != PIPE)
	{
		if (token->type == HERE_DOC)
			cmd->redir->here_doc_expand[i++] = should_expand_here_doc(
					token->next->line);
		token = token->next;
	}
}

void	here_doc_expand_2(t_cmd *cmd, char *lim, int i)
{
	char	*expanded_line;

	expanded_line = NULL;
	while (cmd->minishell->in_here_doc && ft_findstr(lim, cmd->minishell->gnl))
	{
		if (cmd->minishell->gnl)
			free(cmd->minishell->gnl);
		if (expanded_line)
			free(expanded_line);
		cmd->minishell->gnl = get_next_line(0, 0);
		if (cmd->minishell->gnl && ft_findstr(lim, cmd->minishell->gnl))
		{
			expanded_line = strdup_and_free(
					cmd->minishell->gnl, cmd->minishell, "HERE_DOC");
			write(cmd->redir->fd[i], expanded_line, ft_strlen(expanded_line));
		}
		if (!cmd->minishell->gnl || !expanded_line)
			break ;
	}
}

void	here_doc_expand(t_cmd *cmd, char *lim, int i)
{
	char	*file;
	char	*nbr;

	nbr = ft_itoa(cmd->i);
	file = ft_strjoin("/var/tmp/temp", nbr);
	cmd->minishell->in_here_doc = 1;
	cmd->redir->fd[i] = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cmd->redir->fd[i] < 0)
		return (perror("open"), free_ms(cmd->token, NULL, 1));
	here_doc_expand_2(cmd, lim, i);
	cmd->minishell->in_here_doc = 0;
	if (cmd->minishell->gnl)
		free(cmd->minishell->gnl);
	cmd->minishell->gnl = get_next_line(0, 2);
	close(cmd->redir->fd[i]);
	cmd->redir->fd[i] = open(file, O_RDWR, 0644);
	if (cmd->redir->fd[i] < 0)
		return (perror("open"), free_ms(cmd->token, NULL, 1));
	unlink(file);
	free(file);
	free(nbr);
}

void	here_doc(t_cmd *cmd, char *lim, int i)
{
	char	*gnl;
	char	*file;
	char	*nbr;

	cmd->minishell->in_here_doc = 1;
	nbr = ft_itoa(cmd->i);
	file = ft_strjoin("/var/tmp/temp", nbr);
	gnl = get_next_line(0, 1);
	cmd->redir->fd[i] = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (ft_findstr(lim, gnl))
	{
		write(cmd->redir->fd[i], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0, 0);
	}
	free(gnl);
	gnl = get_next_line(0, 2);
	close(cmd->redir->fd[i]);
	cmd->redir->fd[i] = open(file, O_RDWR, 0644);
	unlink(file);
	free(file);
	free(nbr);
	cmd->minishell->in_here_doc = 0;
}
