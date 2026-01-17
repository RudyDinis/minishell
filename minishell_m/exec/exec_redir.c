#include "../minishell.h"

// void here_doc(t_cmd *cmd, char *lim, int i, int *in)
// {
// 	char *gnl;

// 	(*in)++;
// 	gnl = get_next_line(0, 0);
// 	cmd->redir->fd[i] = open("/var/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	if (cmd->redir->fd[i] < 0)
// 		return (free_ms(NULL, cmd, 1));
// 	while (ft_findstr(lim, gnl))
// 	{
// 		write(cmd->redir->fd[i], gnl, ft_strlen(gnl));
// 		free(gnl);
// 		gnl = get_next_line(0, 0);
// 	}
// 	cmd->redir->fd[i] = open("/var/tmp/temp", O_RDWR, 0644);
// 	if (cmd->redir->fd[i] < 0)
// 		return (free_ms(NULL, cmd, 1));

// 	if (dup2(cmd->redir->fd[i], 0) < 0)
// 		return (free_ms(NULL, cmd, 1));
// 	close(cmd->redir->fd[i]);
// 	unlink("/var/tmp/temp");
// }

void redir_out(t_cmd *cmd, char *file, int i, int *out)
{
	(*out)++;
	cmd->redir->fd[i] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(file, W_OK) < 0 && access(file, F_OK) == 0)
		return (perror(file), free_ms(NULL, cmd, 1));
	else if (cmd->redir->fd[i] < 0)
		return (perror(file), free_ms(NULL, cmd, 1));
	else
	{
		if (dup2(cmd->redir->fd[i], 1) < 0)
			return (perror("dup2"), free_ms(NULL, cmd, 1));
		close(cmd->redir->fd[i]);
	}
}

void append(t_cmd *cmd, char *file, int i, int *out)
{
	(*out)++;
	cmd->redir->fd[i] = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(file, W_OK) < 0 && access(file, F_OK) == 0)
		return (perror(file), free_ms(NULL, cmd, 1));
	else if (cmd->redir->fd[i] < 0)
		return (perror(file), free_ms(NULL, cmd, 1));
	{
		if (dup2(cmd->redir->fd[i], 1) < 0)
			return (perror("dup2"), free_ms(NULL, cmd, 1));
		close(cmd->redir->fd[i]);
	}
}

void redir_in(t_cmd *cmd, char *file, int i, int *in)
{
	(*in)++;
	cmd->redir->fd[i] = open(file, O_RDONLY);
	if ((access(file, R_OK) < 0 && access(file, F_OK) == 0))
		return (perror(file), free_ms(NULL, cmd, 1));
	else if (cmd->redir->fd[i] < 0)
		return (perror(file), free_ms(NULL, cmd, 1));
	else
	{
		if (dup2(cmd->redir->fd[i], 0) < 0)
			return (perror("dup2"), free_ms(NULL, cmd, 1));
		close(cmd->redir->fd[i]);
	}
}

void pipe_redirection(t_cmd *cmd, int **fds, int in, int out)
{
	if (cmd->i == 0 && out == 0)
	{
		if (cmd->next)
		{
			if (dup2(fds[0][1], 1) < 0)
				return (perror("dup2"), free_ms(NULL, cmd, 1));
		}
		close(fds[0][1]);
		fds[0][1] = -1;
	}
	if (cmd->i != 0)
	{
		if (in == 0)
		{
			if (dup2(fds[cmd->i - 1][0], 0) < 0)
				return (perror("dup2"), free_ms(NULL, cmd, 1));
			close(fds[cmd->i - 1][0]);
		}
		if (out == 0 && cmd->i < (get_total_cmds(cmd)))
		{
			if (dup2(fds[cmd->i][1], 1) < 0)
				return (perror("dup2"), free_ms(NULL, cmd, 1));
			close(fds[cmd->i][1]);
		}
	}
}

void open_redir(t_cmd *cmd, int **fds)
{
	int (i) = 0;
	int (in) = 0;
	int (out) = 0;

	if (cmd->redir->target)
	{
		while (cmd->redir->target[i])
		{
			if (cmd->redir->redir_type[i] == HERE_DOC)
			{
				dup2(cmd->redir->fd[i], 0);
				close(cmd->redir->fd[i]);
				in++;
			}
			if (cmd->redir->redir_type[i] == REDIR_OUT)
				redir_out(cmd, cmd->redir->target[i], i, &out);
			if (cmd->redir->redir_type[i] == APPEND)
				append(cmd, cmd->redir->target[i], i, &out);
			if (cmd->redir->redir_type[i] == REDIR_IN)
				redir_in(cmd, cmd->redir->target[i], i, &in);
			i++;
		}
	}
	pipe_redirection(cmd, fds, in, out);
}
