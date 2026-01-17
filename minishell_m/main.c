#include "minishell.h"

int is_valid_buf(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (!is_blank(buf[i++]))
			return 1;
	}
	return 0;
}
void	while_read(char **envp)
{
	char	*line;
	char	*prompt;
	t_token *token;

	while (1)
	{
		prompt = write_line();
		line = readline(prompt);
		if (*line && is_valid_buf(line))
		{
			token = create_list(line);
			check_formatting(token, envp);
			free_ms(NULL, token->cmd, -5);
		}
		free(prompt);
		if (*line)
		{
			add_history(line);
		}
		free(line);
	}
}

t_env	*copy_env(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		add_env(&env, envp[i]);
		i++;
	}
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	char		*cwd;

	(void)ac;
	(void)av;
	print_title();
	while_read(envp);
	rl_clear_history();
	return (0);
}



// int main(void)
// {
// 	char *buf;
// 	t_token *token;

// 	while (1)
// 	{
// 		buf = readline("$>");
// 		if (*buf && is_valid_buf(buf))
// 		{
// 			token = create_list(buf);
// 			check_formatting(token);
// 			free_ms(NULL, token->cmd, -5);
// 		}
// 		free(buf);
// 	}
// 	return 0;
// }



	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	// TODO ISATTY
	// TODO AJOUTER L'ENVP POUR LES CMDS
	//TODO GERER LES || ET && ET quotes non fermées ET erreurs de syntaxe corréctement

