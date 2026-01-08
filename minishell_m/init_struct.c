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
	node->s_quotes_prio = 0;
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
		return (NULL);
	tete = head;
	head->index = i++;
	while (i < token_nb)
	{
		head->next = malloc(sizeof(t_token));
		head = head->next;
		init_data_to_null(head);
		head->index = i;
		i++;
	}
	find_type(argv, tete);
	return (tete);
}
