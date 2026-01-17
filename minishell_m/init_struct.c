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

t_token *create_list(char *argv)
{
	int i;
	int token_nb;
	t_token *head;
	t_token *tete;

	token_nb = find_number_of_token(argv);
	i = 0;
	if (token_nb)
		head = ft_calloc(1, sizeof(t_token));;
	if (!head)
		return (exit(1), NULL);
	tete = head;
	head->index = i++;
	while (i < token_nb)
	{
		head->next =  ft_calloc(1, sizeof(t_token));;
		if (!head->next)
			return (free_ms(tete, NULL, 1), NULL);
		head->next->previous = head;
		head = head->next;
		head->index = i++;
	}
	find_type(argv, tete);
	return (tete);
}

t_minishell *init_ms(t_token *token)
{
	t_minishell *minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		free_ms(token, NULL, 1);
	minishell->env =  ft_calloc(1, sizeof(t_env));
	if (!minishell->env)
		free_ms(token, NULL, 1);
	minishell->var =  ft_calloc(1, sizeof(t_var));
	if (!minishell->var)
		free_ms(token, NULL, 1);
	minishell->var->key = ft_strdup("abc");
	minishell->var->value = ft_strdup("a     b     c");
	return (minishell);
}

t_cmd *init_cmd(t_token *token)
{
	t_cmd *cmds;
	t_cmd *head;
	t_minishell *minishell;
	int i;

	cmds =  ft_calloc(1, sizeof(t_cmd));;
	if (!cmds)
		free_ms(token, NULL, 1);
	token->cmd = cmds;
	minishell = init_ms(token);
	head = cmds;
	i = 0;
	while (i < number_of_cmds(token))
	{
		cmds->token = token;
		cmds->minishell = minishell;
		cmds->redir =  ft_calloc(1, sizeof(t_redir));;
		if (!cmds->redir)
			free_ms(token, NULL, 1);
		cmds->i = i;
		if (i + 1 == number_of_cmds(token))
			cmds->next = NULL;
		else
		{
			cmds->next =  ft_calloc(1, sizeof(t_cmd));;
			if (!cmds->next)
				free_ms(token, NULL, 1);
		}
		cmds = cmds->next;
		i++;
	}

	return (head);
}
