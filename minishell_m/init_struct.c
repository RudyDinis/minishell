#include "minishell.h"

t_opcounter init_counter(void)
{
	t_opcounter opcounter;

	opcounter.pipe = 0;
	opcounter.redir_in = 0;
	opcounter.redir_out = 0;
	return (opcounter);
}

t_repere init_repere(void)
{
	t_repere repere;

	repere.in_pipe = 0;
	repere.in_redir_in = 0;
	repere.in_redir_out = 0;
	repere.in_word = 0;
	repere.in_d_quote = 0;
	repere.in_s_quote = 0;
	return (repere);
}

void init_data_to_null(t_token *node)
{
	node->line = NULL;
	node->index = 0;
	node->next = NULL;
	node->in_quotes = 0;
	node->previous = NULL;
}
t_token *create_list(char *argv)
{
	int i;
	t_token *head;
	t_token *tete;
	int token_nb = find_number_of_token(argv);
	i = 0;
	head = NULL;
	if (token_nb)
		head = malloc(sizeof(t_token));
	if (!head)
		return (exit(1), NULL);
	tete = head;
	init_data_to_null(head);
	head->index = i++;
	while (i < token_nb)
	{
		head->next = malloc(sizeof(t_token));
		if (!head->next)
			return (free_ms(tete, NULL, 1, NULL), NULL);
		init_data_to_null(head->next);
		head->next->previous = head;
		head = head->next;
		head->index = i;
		i++;
	}
	find_type(argv, tete);
	return (tete);
}

t_minishell *init_ms(t_cmd *cmd)
{
	t_minishell *minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		free_ms(NULL, cmd, 1, NULL);
	minishell->env = malloc(sizeof(t_env));
	if (!minishell->env)
		free_ms(NULL, cmd, 1, NULL);
	minishell->var = malloc(sizeof(t_var));
	if (!minishell->var)
		free_ms(NULL, cmd, 1, NULL);
	minishell->env->key = NULL;
	minishell->env->next = NULL;
	minishell->env->value = NULL;
	minishell->var->key = "abc";
	minishell->var->next = NULL;
	minishell->var->value = "salut       ça             va";
	return (minishell);
}

t_cmd *init_cmd(t_token *token)
{
	t_cmd *cmds;
	t_cmd *head;
	t_minishell *minishell;
	int i;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
	free_ms(token, NULL, 1, NULL);
	token->cmd = cmds;
	minishell = init_ms(cmds);
	head = cmds;
	i = 0;
	while (i < number_of_cmds(token))
	{
		cmds->args = NULL;
		cmds->cmd = NULL;
		cmds->path = NULL;
		cmds->return_value = 0;
		cmds->token = token;
		cmds->minishell = minishell;
		cmds->redir = malloc(sizeof(t_redir));
		if (!cmds->redir)
			free_ms(token, NULL, 1, NULL);
		cmds->redir->redir_number = 0;
		cmds->redir->redir_type = 0;
		cmds->redir->fd = NULL;
		cmds->redir->target = NULL;
		cmds->i = i;
		if (i + 1 == number_of_cmds(token))
			cmds->next = NULL;
		else
		{
			cmds->next = malloc(sizeof(t_cmd));
			if (!cmds->next)
				free_ms(token, NULL, 1, NULL);
		}
		cmds = cmds->next;
		i++;
	}
	
	return (head);
}
