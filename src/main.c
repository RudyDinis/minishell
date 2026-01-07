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
		printf("%s\n", line);
		free(line);
	}
}

int	main(void)
{
	t_minishell *data;

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
	char *cwd = getcwd(NULL, 0);
	data->pwd = cwd;
	init_signals();
	while_read(data);
	rl_clear_history();
	free(data);
	return (0);
}