#include "minishell.h"

int g_stop;

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

int test(void)
{
	printf("test");
	return 0;
}

void	while_read(char **envp, t_minishell *minishell)
{
	char	*line;
	char	*prompt;
	t_token *token;
	int		exit_value;
	token = NULL;
	while (1)
	{
		init_signals(minishell);
		write_line();
		g_stop = 0;
		line = readline("\001\033[0;32m\002> \001\033[0m\002");
		if (g_stop == 1)
		{
			g_stop = 0;
			add_var(&minishell->var, "?", "130");
		}
		if (g_stop == 2)
		{
			g_stop = 0;
			add_var(&minishell->var, "?", "131");
		}
		if (!line)
		{
				write(1, "exit\n", 5);
				exit_value = ft_atoi(minishell->var->value);
				return (free_minishell(minishell), exit(exit_value));
		}
		if (*line && is_valid_buf(line))
		{
			token = create_list(line);
			if (!token || check_formatting(token, envp, minishell))
			{
				free(line);
				continue ;
			}
			if (token && token->cmd && token->cmd->minishell->exit_status == 1)
				return (free(line), free_ms(NULL, token->cmd, 1));
			if (token && token->cmd)
				free_ms(NULL, token->cmd, -5);
			}
		add_history(line);
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

void shell_lvl(char **envp)
{
	int i;
	int j;
	long lvl;
	char *level;
	char new_shlvl[256];

	i = 0;
	j = 0;
	ft_strcpy(new_shlvl, "SHLVL=");
	while (envp[i] && !ft_strnstr(envp[i], "SHLVL", 5))
		i++;
	if (!envp[i])
		return ;
	while (envp[i][j] && !ft_isdigit(envp[i][j]))
		j++;
	if (!envp[i][j])
		return ;
	lvl = ft_atoi(&envp[i][j]) + 1;
	if (lvl >= 1000)
	{
		ft_printf_error("minishell: warning: shell level (%l) too high, resetting to 1\n", lvl);
		lvl = 1;
	}
	level = ft_itoa(lvl);
	return (ft_strcat(new_shlvl, level), ft_strcpy(envp[i], new_shlvl), free(level));
}

int	main(int ac, char **av, char **envp)
{
	t_minishell *minishell;

	if (!(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)))
		return 0;
	print_title();
	shell_lvl(envp);
	minishell = init_ms(envp);
	if (!minishell)
		exit(1);
	(void)ac;
	(void)av;
	while_read(envp, minishell);
	rl_clear_history();
	return (0);
}

	//TODO HERE DOC LEAKS
	//TODO REDIR DANS REDIR
	// TODO TRANSFORMER TOUS LES INTS EN LONG POUR EVITER LES OVERFLOW

