/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 20:00:58 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_redir(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->redir->target[i])
		i++;
	cmd->redir->fd = malloc(sizeof(int) * (i));
	if (!cmd->redir->fd)
		free_ms(NULL, cmd, 1);
	while (j < i)
		cmd->redir->fd[j++] = -125;
}

int	**malloc_fds(int total_args, t_cmd *cmd)
{
	int	**fds;
	int	i;

	i = 0;
	if (total_args - 1)
		total_args = total_args - 1;
	fds = malloc((total_args) * sizeof(int *));
	if (!fds)
		free_ms(NULL, cmd, 1);
	while (i < (total_args))
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
			return (free_everything_int(fds, i), free_ms(NULL, cmd, 1),
				(int **)1);
		fds[i][0] = -1;
		fds[i][1] = -1;
		i++;
	}
	while (cmd)
	{
		cmd->fds = fds;
		cmd = cmd->next;
	}
	return (fds);
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

int	get_total_cmds(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd->i);
}
