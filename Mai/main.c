#include "minishell.h"

int find_number_of_token(char **argv)
{
	int i;
	int j;
	int token;
	int in_word = 0;
	int in_pipe = 0;
	int in_redir = 0;
	int in_redir_out = 0;

	token = 0;
	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((ft_isalnum(argv[i][j]) || argv[i][j] == '/') && !in_word)
			{
				token++;
				in_word++;
				in_pipe = 0;
				in_redir = 0;
				in_redir_out = 0;
			}
			if (argv[i][j] == '|' && !in_pipe)
			{
				token++;
				in_word = 0;
				in_pipe = 1;
				in_redir = 0;
				in_redir_out = 0;
			}
			if (argv[i][j] == '>' && !in_redir)
			{
				in_word = 0;
				in_pipe = 0;
				in_redir = 1;
				in_redir_out = 0;
				if (argv[i][j + 1] == '>')
					token++;
				else
					token++;
			}
			if (argv[i][j] == '<' && !in_redir_out)
			{
				in_word = 0;
				in_pipe = 0;
				in_redir = 0;
				in_redir_out = 1;
				if (argv[i][j + 1] == '<')
					token++;
				else
					token++;
			}
			j++;
		}
		i++;
	}
	return token;
}

t_repere init_repere(void)
{
	t_repere repere;

	repere.in_pipe = 0;
	repere.in_redir_in = 0;
	repere.in_redir_out = 0;
	repere.in_word = 0;
	return (repere);
}

void increment_repere_2(t_repere *repere, char *str)
{
	if (!ft_findstr(str, "IN_REDIR_IN"))
	{
		repere->in_word = 0;
		repere->in_pipe = 0;
		repere->in_redir_in = 1;
		repere->in_redir_out = 0;
	}
	if (!ft_findstr(str, "IN_REDIR_OUT"))
	{
		repere->in_word = 0;
		repere->in_pipe = 0;
		repere->in_redir_in = 0;
		repere->in_redir_out = 1;
	}
}

void increment_repere(t_repere *repere, char *str)
{
	if (!ft_findstr(str, "IN_WORD"))
	{
		repere->in_word = 1;
		repere->in_pipe = 0;
		repere->in_redir_in = 0;
		repere->in_redir_out = 0;
	}
	if (!ft_findstr(str, "IN_PIPE"))
	{
		repere->in_word = 0;
		repere->in_pipe = 1;
		repere->in_redir_in = 0;
		repere->in_redir_out = 0;
	}
	increment_repere_2(repere, str);
}

int assign_type_redir_edition(char *c, t_token *token, t_repere *repere)
{
	if (c[0] == '>' && !repere->in_redir_out)
	{
		increment_repere(repere, "IN_REDIR_OUT");
		if (c[1] == '>')
			token->type = APPEND;
		else
		{
			printf("Crash : %c\n", c[0]);
			token->type = REDIR_OUT;
		}
		return 1;
	}
	if (c[0] == '<' && !repere->in_redir_in)
	{
		increment_repere(repere, "IN_REDIR_IN");
		if (c[1] == '<')
			token->type = HERE_DOC;
		else
			token->type = REDIR_IN;
		return 1;
	}
	return 0;
}
int assign_type(char *c, t_token *token, t_repere *repere)
{
	if ((ft_isalnum(c[0]) || c[0] == '/') && !repere->in_word)
	{
		increment_repere(repere, "IN_WORD");
		token->type = STR;
		return 1;
	}
	if (c[0] == '|' && !repere->in_pipe)
	{
		increment_repere(repere, "IN_PIPE");
		token->type = PIPE;
		return 1;
	}
	return (assign_type_redir_edition(c, token, repere));
}

void find_type(char **argv, t_token *token)
{
	int i;
	int j;
	t_repere repere;

	repere = init_repere();
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (assign_type(&argv[i][j], token, &repere))
				token = token->next;
			j++;
		}
		i++;
	}
}
/* echo test | wc -l > /std/out */
int main(int argc, char **argv, char **envp)
{
	// int i;
	(void)envp;
	(void)argc;
	t_token *lst = create_list(argv);
	while (lst)
	{
		printf("%d\n", lst->type);
		lst = lst->next;
	}
	return 0;
}
