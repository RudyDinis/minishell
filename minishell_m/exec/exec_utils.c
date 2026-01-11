#include "../minishell.h"

void malloc_redir(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->redir->target[i])
		i++;
	cmd->redir->fd = malloc(sizeof(int) * (i));
	if (!cmd->redir->fd)
		return; // TODO EXIT PROPRE A FAIRE
}

int **malloc_fds(int total_args)
{
	int **fds;
	int i;

	i = 0;
	fds = malloc((total_args) * sizeof(int *));
	while (i < (total_args))
	{
		fds[i] = malloc(2 * sizeof(int));
		i++;
	}
	return (fds);
}

void open_pipes(int **fds, int total_args)
{
	int i;

	i = 0;
	while (i < (total_args))
	{
		pipe(fds[i]);
		i++;
	}
}

void close_all_pipes(int **fds, int total_args)
{
	int i;
	int j;

	i = 0;
	while (i < total_args)
	{
		j = 0;
		while (j < 2)
		{
			close(fds[i][j]);
			j++;
		}
		i++;
	}
}

int get_total_cmds(t_cmd *cmd)
{
	int i;

	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return i;
}
