/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 19:25:02 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_args_size(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	**expanded_args;

	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		k = 0;
		expanded_args = expand_vars(cmd->args[i], cmd->minishell, "EMSE");
		while (expanded_args[k])
		{
			k++;
			j++;
		}
		i++;
		free_everything((void **)expanded_args);
	}
	return (j);
}

char	**expand_args(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	**expanded;
	char	**tmp_expanded;

	i = 0;
	k = 0;
	expanded = malloc((expand_args_size(cmd) + 1) * sizeof(char *));
	if (!expanded)
		free_ms(NULL, cmd, 1);
	while (cmd->args[i])
	{
		j = 0;
		tmp_expanded = expand_vars(cmd->args[i], cmd->minishell, "EMSE");
		while (tmp_expanded[j])
		{
			expanded[k] = ft_strdup(tmp_expanded[j]);
			k++;
			j++;
		}
		i++;
		free_everything((void **)tmp_expanded);
	}
	return (expanded[k] = NULL, free_everything((void **)cmd->args), expanded);
}

void	expander(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->args = expand_args(cmd);
		cmd->cmd = cmd->args[0];
		cmd = cmd->next;
	}
}
