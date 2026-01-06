#include "minishell.h"

void init_data_to_null(t_token *node)
{
	node->line = NULL;
	node->index = 0;
	node->next = NULL;

}
t_token *create_list(char **argv)
{
	int i;
	t_token *head;
	t_token *tete;

	i = 0;
	head = NULL;
	if (find_number_of_token(argv))
		head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	tete = head;
	head->index = i++;
	while (i < find_number_of_token(argv))
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
