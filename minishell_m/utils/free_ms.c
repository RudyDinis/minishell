/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/26 15:26:28 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir(t_redir *redir)
{
	int	i;

	i = 0;
	if (redir)
	{
		if (redir->redir_type)
			free(redir->redir_type);
		if (redir->target)
		{
			if (redir->fd)
			{
				while (redir->target[i])
				{
					if (redir->fd[i] >= 0)
						close(redir->fd[i]);
					i++;
				}
				free(redir->fd);
			}
			free_everything((void **)redir->target);
		}
		if (redir->here_doc_expand)
			free(redir->here_doc_expand);
		free(redir);
	}
}

void	free_token(t_token *token, int n)
{
	if (n == 1 && token->cmd)
		free_cmd(token->cmd, 1);
	while (token->next)
	{
		token = token->next;
		if (token->previous->type == STR)
			free(token->previous->line);
		free(token->previous);
	}
	if (token->type == STR)
		free(token->line);
	free(token);
}

void	free_cmd(t_cmd *cmd, int n)
{
	t_cmd	*head;

	head = cmd;
	if (n == 0 && cmd->token)
		free_token(cmd->token, 0);
	cmd = cmd->next;
	while (head)
	{
		if (head->args)
			free_everything((void **)head->args);
		if (head->path && (head->cmd_found || head->is_absolute))
			free(head->path);
		free_redir(head->redir);
		free(head);
		head = cmd;
		if (cmd)
			cmd = cmd->next;
	}
}

void	free_minishell(t_minishell *data)
{
	t_env	*tmp;
	t_var	*tmp_var;

	while (data->env)
	{
		tmp = data->env->next;
		free(data->env->key);
		free(data->env->value);
		free(data->env);
		data->env = tmp;
	}
	while (data->var)
	{
		tmp_var = data->var->next;
		free(data->var->key);
		free(data->var->value);
		free(data->var);
		data->var = tmp_var;
	}
	if (data->line)
		free(data->line);
	free(data);
}

void	free_ms(t_token *token, t_cmd *cmd, int n)
{
	if (cmd && cmd->fds)
	{
		close_all_pipes(cmd->fds, get_total_cmds(cmd) + 1);
		free_everything_int(cmd->fds, get_total_cmds(cmd) + 1);
	}
	if (token && token->cmd && token->cmd->fds)
	{
		close_all_pipes(token->cmd->fds, get_total_cmds(token->cmd) + 1);
		free_everything_int(token->cmd->fds, get_total_cmds(token->cmd) + 1);
	}
	if (!token)
	{
		if (cmd->minishell && n != -5)
			free_minishell(cmd->minishell);
		free_cmd(cmd, 0);
	}
	if (!cmd)
	{
		if (token->cmd && token->cmd->minishell && n != -5)
			free_minishell(token->cmd->minishell);
		free_token(token, 1);
	}
	if (n != -5)
		exit(n);
}
