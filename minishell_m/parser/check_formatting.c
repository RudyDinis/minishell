#include "../minishell.h"

void check_formatting(t_token *token)
{
	t_token *head;

	head = token;
	while (token)
	{
		if ((token->index == 0 || !token->next) && token->type == PIPE)
			return ("ERROR");
		if ((token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == APPEND || token->type == HERE_DOC)
			&& token->next != STR)
			return ("ERROR");
		if (token->type == PIPE && token->next == PIPE)
			return ("ERROR");
		token = token->next;
	}
}

int get_redir_number(t_token *token, t_cmd *cmd)
{
	int number;
	int redir_number;

	number = 0;
	redir_number = 0;
	while (token)
	{
		if (token->type == PIPE)
		{
			cmd = cmd->next;
			number++;
		}
		if (token->type != STR && token->type != PIPE)
			redir_number++;
		token = token->next;
	}
}

void attributes_redir(t_token *token, t_cmd *cmd)
{
	int redir_number;

	redir_number = get_redir_number(token, cmd);
	while (token)
	{
		if (token->type == PIPE)
			cmd = cmd->next;
	}

}
