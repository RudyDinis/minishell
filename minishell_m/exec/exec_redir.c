#include "../minishell.h"

void here_doc(t_cmd *cmd, char *lim, int i, int *in)
{
	char *gnl;

	(*in)++;
	gnl = get_next_line(0, 0);
	cmd->redir->fd[i] = open("/var/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (ft_findstr(lim, gnl))
	{
		write(cmd->redir->fd[i], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0, 0);
	}
	cmd->redir->fd[i] = open("/var/tmp/temp", O_RDWR, 0644);
	dup2(cmd->redir->fd[i], 0);
	close(cmd->redir->fd[i]);
	unlink("/var/tmp/temp");
}

void redir_out(t_cmd *cmd, char *file, int i, int *out)
{
	(*out)++;
	cmd->redir->fd[i] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(file, W_OK) < 0 && access(file, F_OK) == 0)
		ft_printf("%s: Permission denied\n", cmd->redir->fd[i]);
	else if (cmd->redir->fd[i] < 0)
		ft_printf("%s: a problem has occured with opening outfile\n", cmd->redir->fd[i]);
	else
	{
		dup2(cmd->redir->fd[i], 1);
		close(cmd->redir->fd[i]);
	}
}

void append(t_cmd *cmd, char *file, int i, int *out)
{
	(*out)++;
	cmd->redir->fd[i] = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(file, W_OK) < 0 && access(file, F_OK) == 0)
		ft_printf("%s: Permission denied\n", cmd->redir->fd[i]);
	else if (cmd->redir->fd[i] < 0)
		ft_printf("%s: a problem has occured with opening outfile\n", cmd->redir->fd[i]);
	else
	{
		dup2(cmd->redir->fd[i], 1);
		close(cmd->redir->fd[i]);
	}
}

void redir_in(t_cmd *cmd, char *file, int i, int *in)
{
	(*in)++;
	cmd->redir->fd[i] = open(file, O_RDONLY);
	if ((access(file, R_OK) < 0 && access(file, F_OK) == 0))
		ft_printf("%s: Permission denied\n", file);
	else if (cmd->redir->fd[i] < 0)
		ft_printf("%s: no such file or directory\n", file);
	else
	{
		dup2(cmd->redir->fd[i], 0);
		close(cmd->redir->fd[i]);
	}
}

void pipe_redirection(t_cmd *cmd, int **fds, int in, int out)
{
	int current_proccess;

	current_proccess = cmd->i;
	if (current_proccess == 0 && out == 0)
	{
			dup2(fds[0][1], 1);
			close(fds[0][1]);
	}
	else if (current_proccess != 0)
	{
		if (in == 0)
		{
			dup2(fds[current_proccess - 1][0], 0);
			close(fds[current_proccess - 1][0]);
		}
		if (out == 0)
		{
			dup2(fds[current_proccess - 1][1], 1);
			close(fds[current_proccess - 1][1]);
		}
	}
}

void open_redir(t_cmd *cmd, int **fds)
{
	int i;
	int in;
	int out;

	i = 0;
	in = 0;
	out = 0;
	malloc_redir(cmd);
	while (cmd->redir->target[i])
	{
		if (cmd->redir->redir_type[i] == HERE_DOC)
			here_doc(cmd, cmd->redir->target[i], i, &in);
		else if (cmd->redir->redir_type[i] == REDIR_OUT)
			redir_out(cmd, cmd->redir->target[i], i, &out);
		else if (cmd->redir->redir_type[i] == APPEND)
			append(cmd, cmd->redir->target[i], i, &out);
		else if (cmd->redir->redir_type[i] == REDIR_IN)
			redir_in(cmd, cmd->redir->target[i], i, &in);
		i++;
	}
	pipe_redirection(cmd, fds, in, out);
}
