/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_and_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/25 16:59:23 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_redir_number(t_token *token, t_cmd *cmd)
{
	int	redir_number;

	redir_number = 0;
	while (token)
	{
		if (token->type != STR && token->type != PIPE)
			redir_number++;
		if (token->type == PIPE || !token->next)
		{
			cmd->redir->redir_number = redir_number;
			redir_number = 0;
			cmd = cmd->next;
		}
		token = token->next;
	}
}

void	get_redir_type(t_token *token, t_cmd *cmd, int redir_number)
{
	int	i;

	i = 0;
	if (!redir_number)
		return ;
	cmd->redir->redir_type = malloc(sizeof(t_type) * redir_number);
	if (!cmd->redir->redir_type)
		free_ms(NULL, cmd, 1);
	cmd->redir->target = malloc(sizeof(char *) * (redir_number + 1));
	if (!cmd->redir->target)
		free_ms(NULL, cmd, 1);
	while (token->next && token->type != PIPE)
	{
		if (token->type != STR && token->type != PIPE)
		{
			cmd->redir->redir_type[i] = token->type;
			if (token->type == HERE_DOC)
				cmd->redir->target[i++] = ignore_quotes(token->next->line);
			else
				cmd->redir->target[i++] = strdup_and_free(
						token->next->line, cmd->minishell, "FILE");
		}
		token = token->next;
	}
	cmd->redir->target[i] = NULL;
}

void	attributes_redir(t_token *token, t_cmd *cmd)
{
	t_token	*start_of_cmd;

	start_of_cmd = token;
	while (token && cmd)
	{
		if (token->type == PIPE || !token->next)
		{
			get_redir_type(start_of_cmd, cmd, cmd->redir->redir_number);
			get_here_doc_expand(start_of_cmd, cmd);
			start_of_cmd = token->next;
			cmd = cmd->next;
		}
		token = token->next;
	}
}

void	exec_next(t_token *head, t_minishell *minishell, t_cmd *cmds)
{
	get_redir_number(head, cmds);
	attributes_redir(head, cmds);
	append_args(cmds, head);
	expander(cmds);
	minishell->cmd = cmds;
	launcher(cmds);
}

int	check_formatting(t_token *token, t_minishell *minishell)
{
	t_cmd	*cmds;
	t_token	*head;

	head = token;
	while (token)
	{
		if ((token->index == 0 || !token->next) && token->type == PIPE)
			return (ft_printf_error("syntax error near unexpected token `|'\n"),
				free_ms(head, NULL, -5), 1);
		if ((token->type == REDIR_IN || token->type == REDIR_OUT
				|| token->type == APPEND || token->type == HERE_DOC)
			&& (!token->next || token->next->type != STR))
			return (ft_printf_error(
					"syntax error near unexpected token `newline'\n"),
				free_ms(head, NULL, -5), 1);
		if (token->type == PIPE && token->next && ((token->next->type == PIPE)))
			return (ft_printf_error("syntax error near unexpected token `|'\n"),
				free_ms(head, NULL, -5), 1);
		token = token->next;
	}
	cmds = init_cmd(minishell, head);
	exec_next(head, minishell, cmds);
	return (0);
}
