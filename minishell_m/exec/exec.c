#include "../minishell.h"

void check_access_and_rights(t_cmd *cmd)
{
	if (cmd->is_absolute == 0)
	{
		if (access(cmd->path, F_OK) < 0)
		{
			close(1);
			ft_printf_error("%s: command not found\n", cmd->path);
			free_ms(NULL, cmd, 127);
		}
		if (access(cmd->path, X_OK) < 0)
		{
			close(1);
			ft_printf_error("%s: Permission denied\n", cmd->path);
			free_ms(NULL, cmd, 126);
		}
	}
	if (cmd->is_absolute == 1)
	{
		if (access(cmd->path, F_OK) < 0)
		{
			close(1);
			perror(cmd->path);
			free_ms(NULL, cmd, 127);
		}
		if (access(cmd->path, X_OK) < 0)
		{
			close(1);
			perror(cmd->path);
			free_ms(NULL, cmd, 126);
		}
	}
}

void wait_and_get_return_value(t_cmd *cmd)
{
	int value;
	char *value_str;

	while (cmd)
	{
		waitpid(cmd->pid, &value, 0);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	value_str = ft_itoa(WEXITSTATUS(value));
	add_var(&cmd->minishell->var, "?", value_str);
	free(value_str);
}

void executor(t_cmd *cmd, int **fds, int total_args)
{
	t_cmd *head;

	head = cmd;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			tree_of_closing(fds, cmd->i, total_args);
			open_redir(cmd, fds);
			apply_path(cmd);
			check_access_and_rights(cmd);
			if (execve(cmd->path, cmd->args, cmd->minishell->envp) < 0)
				return (perror(cmd->path), free_ms(cmd->token, NULL, 1));
		}
		cmd = cmd->next;
	}
	close_all_pipes(fds, total_args);
	wait_and_get_return_value(head);
}

void open_here_doc(t_cmd *cmd, int **fds)
{
	int i;
	int j;

	j = 0;
	while (cmd)
	{
		i = 0;
		if (cmd->redir->target)
		{
			malloc_redir(cmd, fds);
			while (cmd->redir->target[i])
			{
				if (cmd->redir->redir_type[i] == HERE_DOC)
				{
					if (cmd->redir->here_doc_expand[j++] == 0)
						here_doc(cmd, cmd->redir->target[i], i);
					else
						here_doc_expand(cmd, cmd->redir->target[i], i);
				}
				i++;
			}
		}
		cmd = cmd->next;
	}
}

void attribute_fds(t_cmd *cmd, int **fds)
{
	while (cmd)
	{
		cmd->fds = fds;
		cmd = cmd->next;
	}
}

void print_args(t_cmd *cmd)
{
	int i;
	while (cmd)
	{
		i = 1;
		while (cmd->args[i])
			printf("ARGS 1 = %s\n", cmd->args[i++]);
		cmd = cmd->next;
	}
}

void launcher(t_cmd *cmd, t_token *token)
{
	int id;
	int **fds;
	int total_args;
	int pipe_last;

	//print_args(cmd);
	total_args = get_total_cmds(cmd) + 1;
	pipe_last = total_args - 1;
	fds = malloc_fds(total_args, cmd);
	open_pipes(fds, total_args);
	attribute_fds(cmd, fds);
	open_here_doc(cmd, fds);
	executor(cmd, fds, total_args);

}
