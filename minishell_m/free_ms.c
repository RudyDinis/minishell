#include "minishell.h"

void free_redir(t_redir *redir)
{
	int i;

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
		free(redir);
	}
}

void free_token(t_token *token, int n)
{
	if (n == 1)
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

void free_cmd(t_cmd *cmd, int n)
{
	t_cmd *head;

	head = cmd;
	if (n == 0)
		free_token(cmd->token, 0);
	cmd = cmd->next;
	while (head)
	{
		if (head->args)
			free_everything((void **)head->args);
		if (head->path)
			free(head->path);
		free_redir(head->redir);
		free(head);
		head = cmd;
		if (cmd)
			cmd = cmd->next;
	}
}

void free_ms(t_token *token, t_cmd *cmd, int n, int **fds)
{
	if (fds)
	{
		if (cmd)
		{
			close_all_pipes(fds, get_total_cmds(cmd) + 1);
			free_everything_int(fds, get_total_cmds(cmd) + 1);
		}
		if (token)
		{
			close_all_pipes(fds, number_of_cmds(token));
			free_everything_int(fds, number_of_cmds(token));
		}
	}
	if (!token)
		free_cmd(cmd, 0);
	if (!cmd)
		free_token(token, 1);
	if (n != -5)
		exit(n);
}
