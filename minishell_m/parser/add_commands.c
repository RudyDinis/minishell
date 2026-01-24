/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:29:40 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_args(t_cmd *cmd, int i)
{
	cmd->args = malloc(sizeof(char *) * (i + 1));
	if (!cmd->args)
		free_ms(NULL, cmd, 1);
	cmd->args[i] = NULL;
}

void	get_args_and_malloc(t_cmd *cmd, t_token *token)
{
	int	i;

	while (token && cmd)
	{
		i = 0;
		if (token->type == PIPE)
			token = token->next;
		while (token->type != PIPE && token->type != STR)
			token = token->next;
		if (token->previous && token->previous->type != PIPE
			&& token->previous->type != STR)
			token = token->next;
		while (token && token->type != PIPE)
		{
			if (!token->previous
				|| (token->previous->type == PIPE && token->type == STR))
				i++;
			if (token->previous && token->previous->type == STR
				&& token->type == STR)
				i++;
			token = token->next;
		}
		malloc_args(cmd, i);
		cmd = cmd->next;
	}
}

void	append_args(t_cmd *cmd, t_token *t)
{
	int	i;

	get_args_and_malloc(cmd, t);
	while (t && cmd)
	{
		i = 0;
		if (t->type == PIPE)
			t = t->next;
		while (t->type != PIPE && t->type != STR)
			t = t->next;
		if (t->previous && t->previous->type != PIPE
			&& t->previous->type != STR)
			t = t->next;
		while (t && t->type != PIPE)
		{
			if (!t->previous
				|| (t->previous->type == PIPE && t->type == STR))
				cmd->args[i++] = ft_strdup(t->line);
			if (t->previous && t->previous->type == STR && t->type == STR)
				cmd->args[i++] = ft_strdup(t->line);
			t = t->next;
		}
		cmd->cmd = cmd->args[0];
		cmd = cmd->next;
	}
}
