#include "minishell.h"

int main(void)
{
	char *buf;
	t_token *lst;
	while (1)
	{
		buf = readline("$>");
		// buf = "< tesuto echo test > test | echo salut";
		lst = create_list(buf);
		check_formatting(lst);
	}
	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	return 0;
}
