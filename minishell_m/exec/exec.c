#include "../minishell.h"


void check_access_and_rights(t_cmd *cmd, int **fds)
{
	if (cmd->is_absolute == 0)
	{
		if (access(cmd->path, F_OK) < 0)
			return (ft_printf_error("%s: command not found\n", cmd->path),
				free_ms(NULL, cmd, 127, fds));
		if (access(cmd->path, X_OK) < 0)
		{
			ft_printf_error("%s: Permission denied\n", cmd->path);
			free_ms(NULL, cmd, 126, fds);
		}
	}
	if (cmd->is_absolute == 1)
	{
		if (access(cmd->path, F_OK) < 0)
		{
			ft_printf_error("%s: No such file or directory\n", cmd->path);
			free_ms(NULL, cmd, 127, fds);
		}
		if (access(cmd->path, X_OK) < 0)
		{
			ft_printf_error("%s: Permission denied\n", cmd->path);
			free_ms(NULL, cmd, 126, fds);
		}
	}
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
			check_access_and_rights(cmd, fds);
			execve(cmd->path, cmd->args, NULL);
			exit(1);
		}
		cmd = cmd->next;
	}
	close_all_pipes(fds, total_args);
	while (head)
	{
		waitpid(head->pid, &head->return_value, 0);
		head->return_value = WEXITSTATUS(head->return_value);
		head = head->next;
	}
}

void here_docw(t_cmd *cmd, char *lim, int i, int **fds)
{
	char *gnl;
	int fd;
	char *file;

	char *nbr = ft_itoa(cmd->i);
	file =  ft_strjoin("/var/tmp/temp", nbr);
	gnl = get_next_line(0, 0);
	cmd->redir->fd[i] = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (ft_findstr(lim, gnl))
	{
		write(cmd->redir->fd[i], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0, 0);
	}
	close(cmd->redir->fd[i]);
	cmd->redir->fd[i] = open(file, O_RDWR, 0644);
	unlink(file);
	free(file);
	free(nbr);
}

void open_here_doc(t_cmd *cmd, int **fds)
{
	int i;

	while (cmd)
	{
		i = 0;
		if (cmd->redir->target)
		{
			malloc_redir(cmd, fds);
			while (cmd->redir->target[i])
			{
				if (cmd->redir->redir_type[i] == HERE_DOC)
					here_docw(cmd, cmd->redir->target[i], i, fds);
				i++;
			}
		}
		cmd = cmd->next;
	}
}

void launcher(t_cmd *cmd, t_token *token)
{
	int id;
	int **fds;
	int total_args;
	int pipe_last;
	t_cmd *head = cmd;

	total_args = get_total_cmds(cmd) + 1;
	pipe_last = total_args - 1;
	fds = malloc_fds(total_args, cmd);
	open_pipes(fds, total_args);
	open_here_doc(cmd, fds);
	executor(cmd, fds, total_args);
	free_ms(token, NULL, -5, fds);
}
