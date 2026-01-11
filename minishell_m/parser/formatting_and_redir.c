#include "../minishell.h"

int number_of_cmds(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i + 1);
}


void get_redir_number(t_token *token, t_cmd *cmd)
{
	int redir_number;

	redir_number = 0;
	while (token)
	{
		if (token->type != STR && token->type != PIPE)
			redir_number++;
		if (token->type == PIPE || !token->next)
		{
			cmd->redir->redir_number = redir_number;
			redir_number = 0;
			cmd = cmd->next;
		}
		token = token->next;
	}
}

void get_redir_type(t_token *token, t_cmd *cmd, int redir_number)
{
	int i;

	i = 0;
	if (!redir_number)
		return ;
	cmd->redir->redir_type = malloc(sizeof(t_type) * redir_number);
	if (!cmd->redir->redir_type)
		return; // TODO GERER L'EXIT;
	cmd->redir->target = malloc(sizeof(char *) * (redir_number + 1));
	if (!cmd->redir->target)
		return; // TODO GERER L'EXIT;
	while (token->next && token->type != PIPE)
	{
		if (token->type != STR && token->type != PIPE)
		{
			cmd->redir->redir_type[i] = token->type;
			cmd->redir->target[i++] = ft_strdup(token->next->line);
		}
		token = token->next;
	}
	cmd->redir->target[i] = NULL;
}

void attributes_redir(t_token *token, t_cmd *cmd)
{
	t_token *start_of_cmd;
	int i;

	start_of_cmd = token;
	i = 0;
	while (token && cmd)
	{
		if (token->type == PIPE || !token->next)
		{
			get_redir_type(start_of_cmd, cmd, cmd->redir->redir_number);
			start_of_cmd = token->next;
			cmd = cmd->next;
		}
		token = token->next;
	}
}

void check_formatting(t_token *token)
{
	t_token *head;
	t_cmd	*cmds;
	int i;
	head = token;
	while (token)
	{
		if ((token->index == 0 || !token->next) && token->type == PIPE)
			return ((void)printf("test"));
		if ((token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == APPEND || token->type == HERE_DOC) && token->next->type != STR)
			return ((void)printf("test"));
		if (token->type == PIPE && token->next->type == PIPE)
			return ((void)printf("test"));
		token = token->next;
	}
	cmds = init_cmd(head);
	get_redir_number(head, cmds);
	attributes_redir(head, cmds);
	append_args(cmds, head);
	execute_cmd(cmds, head);
}
