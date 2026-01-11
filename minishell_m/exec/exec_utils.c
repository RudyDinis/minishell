#include "../minishell.h"

void malloc_redir(t_cmd *cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd->redir->target[i])
	{
		if (cmd->redir->redir_type == HERE_DOC)
			j++;
		i++;
	}
	cmd->redir->fd = malloc(sizeof(int) * (i - j));
	if (!cmd->redir->fd)
		return; // TODO EXIT PROPRE A FAIRE
}
