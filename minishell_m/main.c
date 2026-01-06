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
