/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 19:40:41 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stop;

void	check_stop_and_exit(t_minishell *minishell, char *line)
{
	int	exit_value;

	if (g_stop == 1)
	{
		g_stop = 0;
		add_var(&minishell->var, "?", "130");
	}
	if (!line)
	{
		write(1, "exit\n", 5);
		exit_value = ft_atoi(minishell->var->value);
		return (free_minishell(minishell), exit(exit_value));
	}
}

void	while_read(t_minishell *minishell)
{
	t_token	*token;

	token = NULL;
	while (1)
	{
		init_signals();
		write_line();
		g_stop = 0;
		minishell->line = readline("\001\033[0;32m\002> \001\033[0m\002");
		check_stop_and_exit(minishell, minishell->line);
		if (*minishell->line && is_valid_buf(minishell->line))
		{
			token = create_list(minishell->line);
			if (!token || check_formatting(token, minishell))
			{
				free(minishell->line);
				continue ;
			}
			if (token && token->cmd)
				free_ms(NULL, token->cmd, -5);
		}
		add_history(minishell->line);
		free(minishell->line);
	}
}

t_env	*copy_env(char **envp)
{
	int		i;
	t_env	*env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		add_env(&env, envp[i]);
		i++;
	}
	return (env);
}

void	shell_lvl(char **envp)
{
	int		i;
	int		j;
	long	lvl;
	char	*level;
	char	new_shlvl[256];

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
		ft_printf("warning: shell level (%l) too high, resetting to 1\n", lvl);
		lvl = 1;
	}
	return (level = ft_itoa(lvl), ft_strcat(new_shlvl, level),
		ft_strcpy(envp[i], new_shlvl), free(level));
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;

	(void)ac;
	(void)av;
	if (!(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)))
		return (0);
	print_title();
	shell_lvl(envp);
	minishell = init_ms(envp);
	if (!minishell)
		exit(1);
	while_read(minishell);
	rl_clear_history();
	return (0);
}

// TODO BIEN FAIRE EN SORTE QUE LES BUILT IN INTEGRE LA BONNE RETURN VALUE
