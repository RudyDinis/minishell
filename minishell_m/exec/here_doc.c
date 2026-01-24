#include "../minishell.h"

char *ignore_quotes(char *str)
{
	int i;
	int j;
	char *copy;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			j++;
		i++;
	}
	copy = malloc((i - j) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i])
			copy[j++] = str[i++];
	}
	return (copy[j] = 0, copy);
}

int should_expand_here_doc(char *file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '\'' || file[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

int get_here_doc_nbr(t_token *token)
{
	int i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == HERE_DOC)
			i++;
		token = token->next;
	}
	return (i);
}

void get_here_doc_expand(t_token *token, t_cmd *cmd)
{
	int i;
	int here_doc_nbr;

	i = 0;
	here_doc_nbr = get_here_doc_nbr(token);
	if (!here_doc_nbr)
	{
		cmd->redir->here_doc_expand = NULL;
		return ;
	}
	cmd->redir->here_doc_expand = malloc(here_doc_nbr * sizeof(int));
	if (!cmd->redir->here_doc_expand)
		return (free_ms(cmd->token, NULL, 1));
	while (token && token->type != PIPE)
	{
		if (token->type == HERE_DOC)
			cmd->redir->here_doc_expand[i++] = should_expand_here_doc(token->next->line);
		token = token->next;
	}
}

void here_doc_expand(t_cmd *cmd, char *lim, int i)
{
	int fd;
	char *file;
	char *nbr;
	char *expanded_line;

	expanded_line = NULL;
	nbr = ft_itoa(cmd->i);
	file = ft_strjoin("/var/tmp/temp", nbr);
	cmd->minishell->in_here_doc = 1;
	cmd->redir->fd[i] = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (cmd->minishell->in_here_doc && ft_findstr(lim, cmd->minishell->gnl))
	{
		if (cmd->minishell->gnl)
			free(cmd->minishell->gnl);
		if (expanded_line)
			free(expanded_line);
		cmd->minishell->gnl = get_next_line(0, 0);
		if (cmd->minishell->gnl && ft_findstr(lim, cmd->minishell->gnl))
		{
			expanded_line = strdup_and_free(cmd->minishell->gnl, minishell);
			write(cmd->redir->fd[i], expanded_line, ft_strlen(expanded_line));
		}
		if (!cmd->minishell->gnl || !expanded_line)
			break ;
	}
	cmd->minishell->in_here_doc = 0;
	if (cmd->minishell->gnl)
		free(cmd->minishell->gnl);
	cmd->minishell->gnl = get_next_line(0, 2);;
	close(cmd->redir->fd[i]);
	cmd->redir->fd[i] = open(file, O_RDWR, 0644);
	unlink(file);
	free(file);
	free(nbr);
}

void here_doc(t_cmd *cmd, char *lim, int i)
{
	char *gnl;
	int fd;
	char *file;
	char *nbr;

	cmd->minishell->in_here_doc = 1;
	nbr = ft_itoa(cmd->i);
	file = ft_strjoin("/var/tmp/temp", nbr);
	gnl = get_next_line(0, 1);
	cmd->redir->fd[i] = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (ft_findstr(lim, gnl))
	{
		write(cmd->redir->fd[i], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(0, 0);
	}
	free(gnl);
	gnl = get_next_line(0, 2);
	close(cmd->redir->fd[i]);
	cmd->redir->fd[i] = open(file, O_RDWR, 0644);
	unlink(file);
	free(file);
	free(nbr);
	cmd->minishell->in_here_doc = 0;
}
