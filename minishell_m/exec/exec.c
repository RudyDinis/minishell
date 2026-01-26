/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/26 14:00:03 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_and_get_return_value(t_cmd *cmd)
{
	char	*value_str;

	while (cmd)
	{
		waitpid(cmd->pid, &cmd->minishell->last_cmd_return_value, 0);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	if (WIFSIGNALED(cmd->minishell->last_cmd_return_value)
		&& WCOREDUMP(cmd->minishell->last_cmd_return_value))
	{
		ft_printf_error("Quit (core dumped)\n");
		value_str = ft_itoa(131);
	}
	else if (WTERMSIG(cmd->minishell->last_cmd_return_value) == SIGINT)
		value_str = ft_itoa(130);
	else
		value_str = ft_itoa(WEXITSTATUS(cmd->minishell->last_cmd_return_value));
	add_var(&cmd->minishell->var, "?", value_str);
	free(value_str);
}

void	exec_child(t_cmd *cmd, int **fds, int total_args)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		init_signals_child();
		tree_of_closing(fds, cmd->i, total_args);
		open_redir(cmd, fds);
		check_built_in_child(cmd);
		apply_path(cmd);
		check_access_and_rights(cmd);
		recreate_args_without_empty_quotes(cmd);
		if (execve(cmd->path, cmd->args, cmd->minishell->envp) < 0)
			return (perror(cmd->path), free_ms(cmd->token, NULL, 1));
	}
}

void	executor(t_cmd *cmd, int **fds, int total_args)
{
	int		parent;
	t_cmd	*head;
	char	*value;

	parent = 0;
	head = cmd;
	while (cmd)
	{
		if (check_built_in_parent(cmd))
		{
			parent = 1;
			value = ft_itoa(cmd->minishell->last_cmd_return_value);
			add_var(&cmd->minishell->var, "?", value);
			if (value)
				free(value);
			break ;
		}
		exec_child(cmd, fds, total_args);
		cmd = cmd->next;
	}
	init_signals_parent_exec();
	close_all_pipes(fds, total_args);
	if (!parent)
		wait_and_get_return_value(head);
}

void	attribute_fds(t_cmd *cmd, int **fds)
{
	while (cmd)
	{
		cmd->fds = fds;
		cmd = cmd->next;
	}
}

void	launcher(t_cmd *cmd)
{
	int	**fds;
	int	total_args;

	open_here_doc(cmd);
	if (g_stop)
	{
		g_stop = 0;
		return ;
	}
	total_args = get_total_cmds(cmd) + 1;
	fds = malloc_fds(total_args, cmd);
	open_pipes(fds, total_args);
	attribute_fds(cmd, fds);
	executor(cmd, fds, total_args);
}
