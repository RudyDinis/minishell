#include "../minishell.h"

void pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        return;

    printf("%s\n", cwd);
    free(cwd);
}