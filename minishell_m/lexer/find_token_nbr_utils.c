#include "../minishell.h"

int check_quotes_error(int token, t_repere repere)
{
	if (repere.in_s_quote || repere.in_d_quote)
		printf("incorrect number of quotes"), exit(1); // TODO Faire un truc propre ici;
	else
		return token;
}
