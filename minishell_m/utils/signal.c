/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:28:06 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/24 13:41:32 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:28:06 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 15:03:28 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	char *value;

	(void)sig;
	if (minishell->in_here_doc)
		minishell->g_stop = 1;
	value = ft_strdup("130");
	add_var(&minishell->var, "?", value);
	free(value);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	if (minishell && minishell->cmd)
	{
		if (minishell->cmd->pid == 0)
			write(1, "Quit (core dumped)\n", 19);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void	init_signals_parent_exec(void)
{
	signal(SIGINT, SIG_IGN);
}

void	init_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
}

void	init_signals(t_minishell *data)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 1;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}
