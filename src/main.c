#include "minishell.h"

char	*write_line(t_minishell *data)
{
	char *prompt;
	size_t  prompt_len;
	const char *top;
	const char *bottom; 

	top = GREEN "┌──(" BOLD_BLUE "Minishell" RESET GREEN ")-[" BOLD_WHITE;
	bottom = RESET GREEN "]\n" GREEN "└─" BOLD_BLUE "$ " RESET;
	prompt_len = strlen(top)
				   + strlen(data->pwd)
				   + strlen(bottom)
				   + 1;
    prompt = malloc(prompt_len);
    if (!prompt)
        return (prompt);
    strcpy(prompt, top);
    strcat(prompt, data->pwd);
    strcat(prompt, bottom);
	return (prompt);
}

void	while_read(t_minishell *data) {
	char	*line;
	char 	*prompt;

	while (1)
	{
		prompt = write_line(data);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break;
		if (*line)
			add_history(line);
		free(line);
	}
}

t_env *copy_env(char **envp)
{
    t_env *env = NULL;
    int i = 0;

    while (envp[i])
    {
        add_env(&env, envp[i]);
        i++;
    }
    return env;
}

int	main(int ac, char **av, char **envp)
{
	t_minishell *data;
	char *cwd;
	char *str[2];
	str[0] = "export"; // nom de la commande
	str[1] = NULL;     // pas d’arguments

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_minishell));
	if (!data)
		return 1;
	printf("\033[H\033[J");
	printf(
		BLUE
		"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
		"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
		"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"
		"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
		"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\n\n"
		RESET
	);
	data->env = copy_env(envp);
	export(str, data->env);
	cwd = getcwd(NULL, 0);
	data->pwd = cwd;
	init_signals();
	while_read(data);
	rl_clear_history();
	free(data);
	return (0);
}