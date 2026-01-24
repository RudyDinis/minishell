/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 23:29:12 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd_directory(char *cmd, char **directories)
{
	int		i;
	char	*full_cmd;

	i = 0;
	full_cmd = ft_strtriplejoin(directories[i], "/", cmd);
	if (!full_cmd)
		return (NULL);
	while (directories[i])
	{
		if (access(full_cmd, F_OK) == 0)
			return (free(full_cmd), directories[i]);
		i++;
		free(full_cmd);
		if (directories[i])
			full_cmd = ft_strtriplejoin(directories[i], "/", cmd);
	}
	return (NULL);
}

int	is_absolute(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*find_path(char *cmd, t_cmd *cmds)
{
	char	*path;
	char	*found_directory;
	char	*full_path;
	char	**directories;

	if (is_absolute(cmd))
		return (cmds->is_absolute = 1, ft_strdup(cmd));
	path = get_path_from_env(cmds->minishell->env);
	//path = getenv("PATH")
	if (!path)
		return (cmds->cmd_found = 0, cmd);
	directories = ft_split(path, ":");
	if (!directories)
		return (cmds->cmd_found = 0, cmd);
	found_directory = find_cmd_directory(cmd, directories);
	if (!found_directory)
		return (free_everything((void **)directories),
			cmds->cmd_found = 0, cmd);
	full_path = ft_strtriplejoin(found_directory, "/", cmd);
	if (!full_path)
		return (cmds->cmd_found = 0, cmd);
	return (cmds->cmd_found = 1, free_everything((void **)directories),
		full_path);
}

void	apply_path(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->is_absolute = 0;
		if (cmd->cmd)
			cmd->path = find_path(cmd->cmd, cmd);
		cmd = cmd->next;
	}
}
