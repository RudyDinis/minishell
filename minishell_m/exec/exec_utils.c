/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/25 17:13:18 by bbouarab         ###   ########.fr       */
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

int	get_total_cmds(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd->i);
}

int	get_new_args_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	return (i);
}

void	check_access_and_rights(t_cmd *cmd)
{
	char	*merge;

	if (ft_strcmp("\"\"", cmd->cmd) == 0)
		return (write(2, ": command not found\n", 20),
			free_ms(cmd->token, NULL, 127));
	if (!cmd->path)
		free_ms(cmd->token, NULL, 0);
	if (cmd->is_absolute == 0)
	{
		if (access(cmd->path, F_OK) < 0 || !ft_strchr(cmd->path, '/'))
			return (merge = ft_strjoin(cmd->path, ": command not found\n"),
				ft_printf_error("%s", merge), free(merge),
				free_ms(cmd->token, NULL, 127));
		if (access(cmd->path, X_OK) < 0)
			return (perror(cmd->path), free_ms(cmd->token, NULL, 126));
	}
	if (cmd->is_absolute == 1)
	{
		if (access(cmd->path, F_OK) < 0)
			return (perror(cmd->path), free_ms(cmd->token, NULL, 127));
		if (access(cmd->path, X_OK) < 0 || is_a_directory(cmd))
			return (perror(cmd->path), free_ms(cmd->token, NULL, 126));
	}
}
