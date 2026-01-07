#include "minishell.h"

/* echo test | wc -l > /std/out */
int main(void)
{
	// int i;
	int fd = open("commandes", O_RDWR);
	char buf[256];
	read(fd, buf, 255);
	t_token *lst = create_list(buf);
	while (lst)
	{
		// if (lst->type == 0)
		// 	printf("STR\n");
		// if (lst->type == 1)
		// 	printf("PIPE\n");
		// if (lst->type == 2)
		// 	printf("REDIR_IN\n");
		// if (lst->type == 3)
		// 	printf("REDIR_OUT\n");
		// if (lst->type == 4)
		// 	printf("APPEND\n");
		// if (lst->type == 5)
		// 	printf("HERE_DOC\n");

		printf("%s/", lst->line);
		lst = lst->next;
	}
	return 0;
}
