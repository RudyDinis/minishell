#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"

typedef enum s_type
{
	STR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC
}	t_type;

typedef struct s_token
{
	char *line;
	int index;
	t_type type;
	struct s_token *next;
}	t_token;

typedef struct s_repere
{
	int in_word;
	int in_pipe;
	int in_redir_in;
	int in_redir_out;
} t_repere;

void find_type(char **argv, t_token *token);
t_token *create_list(char **argv);
int find_number_of_token(char **argv);


#endif
