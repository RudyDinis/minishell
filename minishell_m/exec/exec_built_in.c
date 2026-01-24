/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 22:14:44 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	recreate_args_without_empty_quotes(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	new_args = malloc(sizeof(char *) * (get_new_args_size(cmd) + 1));
	while (cmd->args[i])
	{
		if (check_null_in_quotes(cmd->args[i]))
		{
			new_args[j++] = ft_strdup("");
			i++;
		}
		else
			new_args[j++] = ft_strdup(cmd->args[i++]);
	}
	new_args[j] = NULL;
	free_everything((void **)cmd->args);
	cmd->cmd = new_args[0];
	cmd->args = new_args;
}

int	check_built_in_parent(t_cmd *cmd)
{
	if (!cmd->next)
	{
		if (ft_strcmp(cmd->cmd, "cd") == 0)
			return (recreate_args_without_empty_quotes(cmd),
				cd(cmd->args, cmd->minishell), 1);
		if (ft_strcmp(cmd->cmd, "exit") == 0)
			return (recreate_args_without_empty_quotes(cmd),
				exit_shell(cmd, cmd->args), 1);
		if (ft_strcmp(cmd->cmd, "export") == 0)
			return (recreate_args_without_empty_quotes(cmd),
				export(cmd->args, cmd->minishell->env), 1);
		if (ft_strcmp(cmd->cmd, "unset") == 0)
			return (recreate_args_without_empty_quotes(cmd),
				unset(cmd->minishell, cmd->args[1]), 1);
	}
	return (0);
}

void	check_built_in_child(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (recreate_args_without_empty_quotes(cmd),
			echo(cmd->args), free_ms(cmd->token, NULL, 0));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (recreate_args_without_empty_quotes(cmd),
			env(cmd->minishell), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (recreate_args_without_empty_quotes(cmd),
			cd(cmd->args, cmd->minishell), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (recreate_args_without_empty_quotes(cmd),
			exit_shell(cmd, cmd->args));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (recreate_args_without_empty_quotes(cmd),
			export(cmd->args, cmd->minishell->env), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (recreate_args_without_empty_quotes(cmd),
			pwd(), free_ms(NULL, cmd, 0));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (recreate_args_without_empty_quotes(cmd),
			unset(cmd->minishell, cmd->args[1]), free_ms(NULL, cmd, 0));
}
