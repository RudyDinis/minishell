#include "../minishell.h"

void	cd(char **argv, t_minishell *data)
{
	int	res;

	if (!argv[1])
		return ;
	if (argv[2])
	{
		ft_printf_error("cd: too many arguments\n");
		return ;
	}
	res = chdir(argv[1]);
	if (res == 0)
	{
		if (data->pwd)
			free(data->pwd);
		data->pwd = getcwd(NULL, 0);
	}
	else
		perror(argv[1]);
}
