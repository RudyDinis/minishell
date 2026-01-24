/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:30:14 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_redirection_2(t_cmd *cmd, int **fds, int in, int out)
{
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
	pipe_redirection_2(cmd, fds, in, out);
}

void	open_pipes(int **fds, int total_args)
{
	int	i;

	i = 0;
	if (total_args - 1 > 0)
		total_args = total_args - 1;
	while (i < (total_args))
	{
		pipe(fds[i]);
		i++;
	}
}

void	close_all_pipes(int **fds, int total_args)
{
	int	i;
	int	j;

	i = 0;
	if (total_args - 1 > 0)
		total_args = total_args - 1;
	while (i < total_args)
	{
		j = 0;
		while (j < 2)
		{
			if (fds[i][j] >= 0)
			{
				close(fds[i][j]);
				fds[i][j] = -1;
			}
			j++;
		}
		i++;
	}
}
