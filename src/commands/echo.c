#include "../minishell.h"

void echo(char **args, int no_newline)
{
    int i = 1;

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (!no_newline)
        printf("\n");
}
