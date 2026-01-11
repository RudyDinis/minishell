#include "../minishell.h"


void executor(t_cmd *cmd, int **fds, int total_args)
{
	t_cmd *head;
	char *commande = ft_strjoin("/usr/bin/", cmd->cmd);
	head = cmd;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			tree_of_closing(fds, cmd->i, total_args);
			open_redir(cmd, fds);
		}
		cmd = cmd->next;
	}
	while (head)
	{
		waitpid(head->pid, 0, 1);
		head = head->next;
	}
}

void launcher(t_cmd *cmd, t_token *token)
{
	int id;
	int **fds;
	int total_args;
	int pipe_last;

	total_args = get_total_cmds(cmd);
	pipe_last = total_args - 1;
	fds = malloc_fds(pipe_last);
	open_pipes(fds, pipe_last);
	executor(cmd, fds, total_args);
	close_all_pipes(fds, pipe_last);
	// printf("%d", total_args);
}
