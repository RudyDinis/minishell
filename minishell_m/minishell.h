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
	char	*line;
	int		s_quotes_prio;
	int		index;
	t_type type;
	struct s_token *next;
}	t_token;

typedef struct s_repere
{
	int in_s_quote;
	int in_d_quote;
	int in_word;
	int in_pipe;
	int in_redir_in;
	int in_redir_out;
} t_repere;

void find_type(char *buf, t_token *token);
char *extract_word(char *buf);
t_token *create_list(char *buf);
int find_number_of_token(char *buf);
int assign_type(char *c, t_token *token, t_repere *repere);
t_repere init_repere(void);
int check_quotes_error(int token, t_repere repere);

#endif
