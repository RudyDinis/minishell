/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:36:22 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/15 13:49:59 by rdinis           ###   ########.fr       */
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
	data->env = copy_env(envp);
	data->last_cmd_return_value = 0;
	add_var(&data->var, "test", "salut     ça     va");
	char ** test = expand_vars("'$test \"test\"'", data, "FILE");
	int i = 0;
	while (test[i])
		printf("%s", test[i++]);
	cwd = getcwd(NULL, 0);
	data->pwd = cwd;
	init_signals();
	while_read(data);
	rl_clear_history();
	free(data);
	return (0);
}
