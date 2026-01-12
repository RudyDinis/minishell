#include "../minishell.h"

void malloc_redir(t_cmd *cmd, int **fds)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd->redir->target[i])
		i++;
	cmd->redir->fd = malloc(sizeof(int) * (i));
	if (!cmd->redir->fd)
		free_ms(NULL, cmd, 1, fds);
	while (j < i)
		cmd->redir->fd[j++] = -125;
}

int **malloc_fds(int total_args, t_cmd *cmd)
{
	int **fds;
	int i;

	i = 0;
	fds = malloc((total_args) * sizeof(int *));
	if (!fds)
		free_ms(NULL, cmd, 1, NULL);
	while (i < (total_args))
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
		{
			free_everything_int(fds, i);
			free_ms(NULL, cmd, 1, NULL);
		}
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
	while (cmd->next)
		cmd = cmd->next;
	return cmd->i;
}
