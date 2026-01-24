/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 20:00:49 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_out(t_cmd *cmd, char *file, int i, int *out)
{
	(*out)++;
	cmd->redir->fd[i] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(file, W_OK) < 0 && access(file, F_OK) == 0)
		return (perror(file), free_ms(cmd->token, NULL, 126));
	else if (cmd->redir->fd[i] < 0)
		return (perror(file), free_ms(cmd->token, NULL, 127));
	else
	{
		if (dup2(cmd->redir->fd[i], 1) < 0)
			return (close(cmd->redir->fd[i]), perror("dup2"),
				free_ms(cmd->token, NULL, 1));
		close(cmd->redir->fd[i]);
		cmd->redir->fd[i] = -1;
	}
}

void	append(t_cmd *cmd, char *file, int i, int *out)
{
	(*out)++;
	cmd->redir->fd[i] = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(file, W_OK) < 0 && access(file, F_OK) == 0)
		return (perror(file), free_ms(NULL, cmd, 126));
	else if (cmd->redir->fd[i] < 0)
		return (perror(file), free_ms(NULL, cmd, 127));
	{
		if (dup2(cmd->redir->fd[i], 1) < 0)
			return (perror("dup2"), free_ms(NULL, cmd, 1));
		close(cmd->redir->fd[i]);
		cmd->redir->fd[i] = -1;
	}
}

void	redir_in(t_cmd *cmd, char *file, int i, int *in)
{
	(*in)++;
	cmd->redir->fd[i] = open(file, O_RDONLY);
	if ((access(file, R_OK) < 0 && access(file, F_OK) == 0))
		return (perror(file), free_ms(cmd->token, NULL, 126));
	else if (cmd->redir->fd[i] < 0)
		return (perror(file), free_ms(cmd->token, NULL, 1));
	else
	{
		if (dup2(cmd->redir->fd[i], 0) < 0)
			return (perror("dup2"), free_ms(cmd->token, NULL, 1));
		close(cmd->redir->fd[i]);
		cmd->redir->fd[i] = -1;
	}
}

void	pipe_redirection(t_cmd *cmd, int **fds, int in, int out)
{
	if (cmd->i == 0 && out == 0)
	{
		if (cmd->next)
		{
			if (dup2(fds[0][1], 1) < 0)
				return (perror("dup2"), free_ms(cmd->token, NULL, 1));
		}
	}
	if (cmd->i == 0)
	{
		close(fds[0][1]);
		fds[0][1] = -1;
	}
	if (cmd->i != 0)
	{
		if (in == 0)
		{
			if (dup2(fds[cmd->i - 1][0], 0) < 0)
				return (perror("dup2"), free_ms(cmd->token, NULL, 1));
		}
		close(fds[cmd->i - 1][0]);
		fds[cmd->i - 1][0] = -1;
		if (out == 0 && cmd->i < (get_total_cmds(cmd)))
		{
			if (dup2(fds[cmd->i][1], 1) < 0)
				return (perror("dup2"), free_ms(cmd->token, NULL, 1));
			close(fds[cmd->i][1]);
			fds[cmd->i][1] = -1;
		}
	}
}

void	open_redir(t_cmd *cmd, int **fds)
{
	int (i) = 0;
	int (in) = 0;
	int (out) = 0;
	if (cmd->redir->target)
	{
		while (cmd->redir->target[i])
		{
			if (cmd->redir->redir_type[i] == HERE_DOC)
			{
				dup2(cmd->redir->fd[i], 0);
				close(cmd->redir->fd[i]);
				cmd->redir->fd[i] = -1;
				in++;
			}
			if (cmd->redir->redir_type[i] == REDIR_OUT)
				redir_out(cmd, cmd->redir->target[i], i, &out);
			if (cmd->redir->redir_type[i] == APPEND)
				append(cmd, cmd->redir->target[i], i, &out);
			if (cmd->redir->redir_type[i] == REDIR_IN)
				redir_in(cmd, cmd->redir->target[i], i, &in);
			i++;
		}
	}
	pipe_redirection(cmd, fds, in, out);
}
