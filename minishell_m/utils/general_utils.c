/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:34:04 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/24 22:40:18 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	number_of_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i + 1);
}

char	*strdup_and_free(char *line, t_minishell *minishell, char *param)
{
	char	**expanded;
	char	*redir;

	expanded = expand_vars(line, minishell, param);
	redir = ft_strdup(expanded[0]);
	free_everything((void **)expanded);
	return (redir);
}

int	is_valid_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (!v(buf[i++]))
			return (1);
	}
	return (0);
}
