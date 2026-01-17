#include "../minishell.h"

void	cd(char **argv, t_minishell *data)
{
	int	res;

	res = chdir(argv[1]);
	if (res == 0)
		data->pwd = getcwd(NULL, 0);
	else
		printf("Cannot open this directory\n");
}
