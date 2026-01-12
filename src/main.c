/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:36:22 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/12 16:36:30 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	while_read(t_minishell *data)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = write_line(data);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (*line)
		{
			cd("./utils", data);
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
	t_minishell	*data;
	char		*cwd;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_minishell));
	if (!data)
		return (1);
	print_title();
	printf("\n%s\n", check_and_replace("\"test $a '$a' $\"", data));
	data->env = copy_env(envp);
	cwd = getcwd(NULL, 0);
	data->pwd = cwd;
	init_signals();
	while_read(data);
	rl_clear_history();
	free(data);
	return (0);
}
