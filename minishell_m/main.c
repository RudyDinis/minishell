#include "minishell.h"

/* echo test | wc -l > /std/out */
int main(void)
{
	// int i
	int fd = open("commandes", O_RDWR);
	char buf[256];
	memset(buf, '\0', 256);
	read(fd, buf, 255);
	char *tst = "< wc -l > /std/out >> text >> >";
	t_token *lst = create_list(buf);
	//TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	// while (lst)
	// {
	// 	printf("%s ", lst->line);
	// 	lst = lst->next;
	// }
	check_formatting(lst);

	return 0;
}
