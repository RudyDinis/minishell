#include "minishell.h"

int main(void)
{
	char *test[] = {"pwd", "-h", NULL};
	execve("/usr/bin/pwd", test, NULL);
}
