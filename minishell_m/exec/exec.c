#include "../minishell.h"

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


void executor(t_cmd *cmd, int **fds, int total_args)
{
	int i;

	i = 0;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			tree_of_closing(fds, i, total_args)
		}
		cmd = cmd->next;
		i++;
	}
}

void launcher(t_cmd *cmd, t_token *token)
{
	int id;
	int **fds;
	int total_args;
	int pipe_last;

	total_args = number_of_cmds(token);
	pipe_last = total_args - 1;
	fds = malloc_fds(pipe_last);
	open_pipes(fds, pipe_last);
	exec(cmd, fds, total_args);
	close_all_pipes(fds, pipe_last);
	// printf("%d", total_args);
}
