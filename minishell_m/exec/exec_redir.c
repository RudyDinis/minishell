#include "../minishell.h"

void here_doc(char *lim);
{
	int here;
	char *gnl;

	gnl = get_next_line(0);
	here = open("/var/tmp/temp", O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (ft_findstr(lim, gnl))
	{
		write(here, gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0);
	}
	here = open("/var/tmp/temp", O_RDWR, 0644);
	dup2(here, 0);
	close(here);
	unlink("/var/tmp/temp");
}

void redir_out(t_cmd *cmd, char *file, int j)
{
	cmd->redir->fd[j] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(cmd->redir->fd[j], W_OK) < 0 && access(cmd->redir->fd[j], F_OK) == 0)
		ft_printf("%s: Permission denied\n", cmd->redir->fd[j]);
	else if (cmd->redir->fd[j] < 0)
		ft_printf("%s: a problem has occured with opening outfile\n", cmd->redir->fd[j]);
	else
	{
		dup2(cmd->redir->fd[j], 1);
		close(cmd->redir->fd[j]);
	}
}

void append(t_cmd *cmd, char *file, int j)
{
	cmd->redir->fd[j] = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(cmd->redir->fd[j], W_OK) < 0 && access(cmd->redir->fd[j], F_OK) == 0)
		ft_printf("%s: Permission denied\n", cmd->redir->fd[j]);
	else if (cmd->redir->fd[j] < 0)
		ft_printf("%s: a problem has occured with opening outfile\n", cmd->redir->fd[j]);
	else
	{
		dup2(cmd->redir->fd[j], 1);
		close(cmd->redir->fd[j]);
	}
}

void redir_in(t_cmd *cmd, char *file, int j)
{
	cmd->redir->fd[j] = open(file, O_RDONLY);
	if ((access(file, R_OK) < 0 && access(file, F_OK) == 0))
		ft_printf("%s: Permission denied\n", file);
	else if (cmd->redir->fd[j] < 0)
		ft_printf("%s: no such file or directory\n", file);
	else
	{
		dup2(cmd->redir->fd[j], 0);
		close(cmd->redir->fd[j]);
	}
}
}

void open_redir(t_cmd *cmd)
{
	int i;
	int j;

	j = 0;
	i = 0;
	malloc_redir(cmd);
	while (cmd->redir->target[i])
	{
		if (cmd->redir->redir_type == HERE_DOC)
			here_doc(cmd->redir->target[i]);
		else if (cmd->redir->redir_type == REDIR_OUT)
			redir_out(cmd, cmd->redir->target[i], j);
		else if (cmd->redir->redir_type == APPEND)
			append(cmd, cmd->redir->target[i], j);
		else if (cmd->redir->redir_type == REDIR_IN)
			redir_in(cmd, cmd->redir->target[i], j);
		i++;
		j++;
	}
}
