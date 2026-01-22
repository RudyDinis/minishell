#include "../minishell.h"

void check_access_and_rights(t_cmd *cmd, int **fds)
{
	char *merge;

	if (!cmd->path)
		return (write(2,": command not found\n", 20), free_ms(cmd->token, NULL, 127));
	if (cmd->is_absolute == 0)
	{
		if (access(cmd->path, F_OK) < 0)
			return (merge = ft_strjoin(cmd->path, ": command not found\n"),
				ft_printf_error("%s", merge), free(merge), free_ms(cmd->token, NULL, 127));
		if (access(cmd->path, X_OK) < 0)
			return (perror(cmd->path), free_ms(NULL, cmd, 126));
	}
	if (cmd->is_absolute == 1)
	{
		if (access(cmd->path, F_OK) < 0)
			return (perror(cmd->path), free_ms(NULL, cmd, 127));
		if (access(cmd->path, X_OK) < 0)
			return (perror(cmd->path), free_ms(NULL, cmd, 126));
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
			break;
		cmd = cmd->next;
	}
	value_str = ft_itoa(WEXITSTATUS(value));
	add_var(&cmd->minishell->var, "?", value_str);
	free(value_str);
}

int check_built_int_parent(t_cmd *cmd)
{
	if (!cmd->next)
	{
		if (ft_strcmp(cmd->cmd, "cd") == 0)
			return (cd(cmd->args, cmd->minishell), cmd->minishell->last_cmd_return_value = 0, 1);
		if (ft_strcmp(cmd->cmd, "exit") == 0)
			return (exit_shell(cmd, cmd->args), 1);
		if (ft_strcmp(cmd->cmd, "export") == 0)
			return (export(cmd->args, cmd->minishell->env), cmd->minishell->last_cmd_return_value = 0, 1);
		if (ft_strcmp(cmd->cmd, "unset") == 0)
			return (unset(cmd->minishell, cmd->args[1]), cmd->minishell->last_cmd_return_value = 0, 1);
	}
	return 0;
}

void check_built_int_child(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (echo(cmd->args), close(0), close(1), free_ms(cmd->token, NULL, 0));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (env(cmd->minishell), close(0), close(1), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (cd(cmd->args, cmd->minishell), close(0), close(1), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (close(0), close(1), exit_shell(cmd, cmd->args));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (export(cmd->args, cmd->minishell->env), close(0), close(1), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (pwd(), close(0), close(1), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (unset(cmd->minishell, cmd->args[1]), close(0), close(1), free_ms(NULL, cmd, 0));
}

void executor(t_cmd *cmd, int **fds, int total_args)
{
	t_cmd *head;
	int parent;

	parent = 0;
	head = cmd;
	while (cmd)
	{
		if (check_built_int_parent(cmd))
		{
			parent = 1;
			break;
		}
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			init_signals_child();
			tree_of_closing(fds, cmd->i, total_args);
			open_redir(cmd, fds);
			check_built_int_child(cmd);
			apply_path(cmd);
			check_access_and_rights(cmd, fds);
			if (execve(cmd->path, cmd->args, NULL) < 0)
				return (perror(cmd->path), free_ms(cmd->token, NULL, 1));
		}
		cmd = cmd->next;
	}
	init_signals_parent_exec();
	close_all_pipes(fds, total_args);
	if (!parent)
		wait_and_get_return_value(head);
}

void open_here_doc(t_cmd *cmd)
{
	int i;
	int j;

	j = 0;
	while (cmd)
	{
		i = 0;
		j = 0;
		if (cmd->redir->target)
		{
			malloc_redir(cmd);
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

	print_args(cmd);
	open_here_doc(cmd);
	if (cmd->minishell->g_stop)
	{
		cmd->minishell->g_stop = 0;
		return ;
	}
	total_args = get_total_cmds(cmd) + 1;
	fds = malloc_fds(total_args, cmd);
	open_pipes(fds, total_args);
	attribute_fds(cmd, fds);
	executor(cmd, fds, total_args);
}
