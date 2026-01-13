#include "../minishell.h"

int expand_args_size(t_cmd *cmd)
{
	char **expanded_args;
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		expanded_args = expand_vars(cmd->args[i], cmd->minishell);
		while (expanded_args[j++])
			;
		free_everything((void **)expanded_args);
		i++;
	}
	return j;
}

char **expand_args(t_cmd *cmd)
{
	char **expanded_args;
	char **tmp_expanded;
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	tmp_expanded = expand_vars(cmd->args[i], cmd->minishell);
	expanded_args = malloc((expand_args_size(cmd) + 1) * sizeof(char *));
	if (!expand_args)
		free_ms(NULL, cmd, 1, NULL);
	expanded_args[expand_args_size(cmd)] = 0;
	while (cmd->args[i])
	{
		j = 0;
		while (tmp_expanded[j])
		{
			expanded_args[k] = ft_strdup(tmp_expanded[j]);
			k++;
			j++;
		}
		if (!expanded_args[k - 1])
			free_ms(NULL, cmd, 1, NULL);
		i++;
		free_everything((void **)tmp_expanded);
	}
	return (expanded_args);
}
void expander(t_cmd *cmd)
{
	while (cmd)
	{
		free_everything((void **)cmd->args);
		cmd->args = expand_args(cmd);
		cmd->cmd = cmd->args[0];
		cmd = cmd->next;
	}
}
