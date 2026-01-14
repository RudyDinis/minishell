#include "../minishell.h"

int expand_args_size(t_cmd *cmd)
{
	char **expanded_args;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		k = 0;
		expanded_args = expand_vars(cmd->args[i], cmd->minishell, "EMSE");
		while (expanded_args[k])
		{
			k++;
			j++;
		}
		i++;
		free_everything((void **)expanded_args);
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
	expanded_args = malloc((expand_args_size(cmd) + 1) * sizeof(char *));
	if (!expanded_args)
		free_ms(NULL, cmd, 1, NULL);
	expanded_args[expand_args_size(cmd)] = NULL;
	while (cmd->args[i])
	{
		j = 0;
		tmp_expanded = expand_vars(cmd->args[i], cmd->minishell, "EMSE");
		while (tmp_expanded[j])
		{
			expanded_args[k] = ft_strdup(tmp_expanded[j]);
			k++;
			j++;
		}
		i++;
		free_everything((void **)tmp_expanded);
	}
	free_everything((void **)cmd->args);
	return (expanded_args);
}
void expander(t_cmd *cmd)
{
	while (cmd)
	{
		//free_everything((void **)cmd->args);
		cmd->args = expand_args(cmd);
		printf("la commande = %s\n", cmd->args[0]);
		printf("le param est = %s\n", cmd->args[1]);
		cmd->cmd = cmd->args[0];
		cmd = cmd->next;
	}
}
