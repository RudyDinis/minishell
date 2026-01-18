#include "../minishell.h"

static void	close_first_process(int **fds, int total_args)
{
	int	i;
	int	j;

	close(fds[0][0]);
	fds[0][0] = -1;
	i = 1;
	while (i < total_args)
	{
		j = 0;
		while (i < total_args && j < 2)
		{
			close(fds[i][j]);
			fds[i][j++] = -1;
		}
		i++;
	}
}

static void	close_middle_process(int **fds, int current_process, int total_args)
{
	int	i;
	int	j;

	i = 0;
	while (i < total_args)
	{
		j = 0;
		if (i == (current_process - 1))
		{
			close(fds[i][1]);
			fds[i++][1] = -1;
		}
		if (i == (current_process))
		{
			close(fds[i][0]);
			fds[i++][0] = -1;
		}
		while (i < total_args && j < 2)
		{
			close(fds[i][j]);
			fds[i][j++] = -1;
		}
		i++;
	}
}

static void	close_last_process(int **fds, int current_process, int total_args)
{
	int	i;
	int	j;

	i = 0;
	while (i < total_args)
	{
		j = 0;
		if (i == (current_process - 1))
		{
			close(fds[i][1]);
			fds[i][1] = -1;
			i++;
		}
		while (i < total_args && j < 2)
		{
			close(fds[i][j]);
			fds[i][j++] = -1;
		}
		i++;
	}
}

void	tree_of_closing(int **fds, int current_process, int total_args)
{
	if (total_args - 1 > 0)
		total_args = total_args - 1;
	if (current_process == 0)
		close_first_process(fds, total_args);
	else if (current_process != 0 && current_process < (total_args))
		close_middle_process(fds, current_process, total_args);
	else if (current_process != 0 && current_process == (total_args))
		close_last_process(fds, current_process, total_args);
}
