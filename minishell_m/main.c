#include "minishell.h"

/* echo test | wc -l > /std/out */
int main(void)
{
	// int i
	int fd = open("commandes", O_RDWR);
	char buf[256];
	read(fd, buf, 255);
	char *tst = "< wc -l > /std/out >> text >> >";
	t_token *lst = create_list(buf);
	while (lst)
	{
		// if (lst->type == 0)
		// 	printf("STR ");
		// if (lst->type == 1)
		// 	printf("| ");
		// if (lst->type == 2)
		// 	printf("< ");
		// if (lst->type == 3)
		// 	printf("> ");
		// if (lst->type == 4)
		// 	printf(">> ");
		// if (lst->type == 5)
		// 	printf("<< ");

		printf("%s ", lst->line);
		// if (lst->s_quotes_prio)
		// 	printf("- SHOULDN'T EXPAND\n");
		// else
		// 	printf("- YES SHOULD EXPAND\n");
		lst = lst->next;
	}
	return 0;
}
