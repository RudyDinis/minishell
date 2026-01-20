#include "minishell.h"

t_minishell *minishell;

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
void	while_read(char **envp, t_minishell *minishell)
{
	char	*line;
	char	*prompt;
	t_token *token;

	token = NULL;
	if (isatty(0))
	{
		while (1)
		{
			prompt = write_line();
			line = readline(prompt);
			free(prompt);
			if (!line)
			{
					write(1, "exit\n", 5);
					free_minishell(minishell), exit(1);
			}
			if (*line && is_valid_buf(line))
			{
				token = create_list(line);
				if (!token || check_formatting(token, envp, minishell))
					continue ;
				if (token && token->cmd && token->cmd->minishell->exit_status == 1)
					return (free(line), free_ms(NULL, token->cmd, 1));
				if (token && token->cmd)
					free_ms(NULL, token->cmd, -5);
				add_history(line);
				free(line);
			}
		}
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

	minishell = init_ms(envp);
	if (!minishell)
		exit(1);
	(void)ac;
	(void)av;
	init_signals(minishell);
	print_title();
	while_read(envp, minishell);
	rl_clear_history();
	return (0);
}

	//TODO GERER L'OVERLAPPING DES MESSAGES D'ERREURS
	//TODO IMPLEMENTER SHLVL + 1;
	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW
	// TODO ISATTY
	//TODO GERER LES || ET && ET quotes non fermées ET erreurs de syntaxe corréctement

