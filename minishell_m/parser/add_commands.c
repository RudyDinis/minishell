#include "../minishell.h"

void malloc_args(t_cmd *cmd, int i)
{
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		free_ms(NULL, cmd, 1);
	cmd->args[i] = NULL;
	// cmd->cmd = cmd->args[0];
}

int get_number_args(t_cmd *cmd, t_token *token)
{
	int i;

	i = 0;
	while (token && cmd)
	{
		if (token->type == PIPE)
			token = token->next;
		while (token->type != PIPE && token->type != STR)
			token = token->next;
		if (token->previous && token->previous->type != PIPE && token->previous->type != STR)
			token = token->next;
		while (token && token->type != PIPE)
		{
			if (token->type != PIPE && token->type != STR)
			{
				token = token->next;
				if (token && !token->next)
					break;
				token = token->next;
			}
			i++;
			token = token->next;
		}
		malloc_args(cmd, i);
		cmd = cmd->next;
		i = 0;
		while (token && token->type != PIPE)
			token = token->next;
	}
}
void append_args(t_cmd *cmd, t_token *token)
{
	int i;

	i = 0;
	get_number_args(cmd, token);
	while (token && cmd)
	{
		if (token->type == PIPE)
			token = token->next;
		while (token->type != PIPE && token->type != STR)
			token = token->next;
		if (token->previous && token->previous->type != PIPE && token->previous->type != STR)
			token = token->next;
		while (token && token->type != PIPE)
		{
			if (token->type != PIPE && token->type != STR)
			{
				token = token->next;
				if (token && !token->next)
					break;
				token = token->next;
			}
			cmd->args[i++] = ft_strdup(token->line);
			token = token->next;
		}
		i = 0;
		cmd->cmd = cmd->args[0];
		cmd = cmd->next;
		while (token && token->type != PIPE)
			token = token->next;
	}
}
