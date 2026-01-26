#include "../minishell.h"

int	expand_args_size(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	**expanded;

	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		k = 0;
		if (!ft_findstr(cmd->cmd, "export"))
			expanded = expand_vars(cmd->args[i], cmd->minishell, "HERE_DOC");
		else
			expanded = expand_vars(cmd->args[i], cmd->minishell, "ELSE");
		while (expanded[k])
		{
			k++;
			j++;
		}
		i++;
		free_everything((void **)expanded);
	}
	return (j);
}

char	**expand_args(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	**expanded;
	char	**tmp_expanded;

	i = 0;
	k = 0;
	expanded = malloc((expand_args_size(cmd) + 1) * sizeof(char *));
	if (!expanded)
		free_ms(NULL, cmd, 1);
	while (cmd->args[i])
	{
		j = 0;
		if (!ft_findstr(cmd->cmd, "export"))
			tmp_expanded = expand_vars(cmd->args[i], cmd->minishell, "HERE_DOC");
		else
			tmp_expanded = expand_vars(cmd->args[i], cmd->minishell, "ELSE");
		while (tmp_expanded[j])
			expanded[k++] = ft_strdup(tmp_expanded[j++]);
		i++;
		free_everything((void **)tmp_expanded);
	}
	return (expanded[k] = NULL, free_everything((void **)cmd->args), expanded);
}

void	expander(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->args = expand_args(cmd);
		cmd->cmd = cmd->args[0];
		cmd = cmd->next;
	}
}