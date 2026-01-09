#include "../minishell.h"

int get_quotes_size(char *buf, char c)
{
	int i;
	int quote;
	size_t j;

	quote = 0;
	i = 1;
	j = 0;
	while (buf[i])
	{
		if (buf[i] == c)
		{
			quote++;
			i++;
		}
		if (quote && buf[i] == ' ')
			break;
		j++;
		i++;
	}
	return j;
}
char *extract_word_dquotes(char *buf)
{
	int i;
	int quote;
	size_t j;
	char *line;

	i = 1;
	j = 0;
	quote = 0;
	line = malloc(get_quotes_size(buf, '\"') + 1);
	if (!line)
		return (NULL);
	while (buf[i])
	{
		if (buf[i] == '\"')
		{
			quote++;
			i++;
		}
		if (quote && buf[i] == ' ')
			break;
		line[j++] = buf[i++];
	}
	return (line[j] = 0, line);
}

char *extract_word_squotes(char *buf)
{
	int i;
	int quote;
	size_t j;
	char *line;

	i = 1;
	j = 0;
	quote = 0;
	line = malloc(get_quotes_size(buf, '\'') + 1);
	if (!line)
		return (NULL);
	while (buf[i])
	{
		if (buf[i] == '\'')
		{
			quote++;
			i++;
		}
		if (quote && buf[i] == ' ')
			break;
		line[j++] = buf[i++];
	}
	return (line[j] = 0, line);
}

void extract_word_check_quotes(char buf, t_repere *repere)
{
	if (buf == '\'' && !repere->in_d_quote)
	{
		if ((buf == '\'') && repere->in_s_quote)
			repere->in_s_quote = 0;
		else
			repere->in_s_quote = 1;
	}
	if (buf == '\"' && !repere->in_s_quote)
	{
		if ((buf == '\"') && repere->in_d_quote)
			repere->in_d_quote = 0;
		else
			repere->in_d_quote = 1;
	}
}

int extract_size(char *buf)
{
	t_repere repere;
	int i;

	i = 0;
	repere = init_repere();
	while (buf[i])
	{
		extract_word_check_quotes(buf[i], &repere);
		if ((!repere.in_s_quote && !repere.in_d_quote) && (is_blank(buf[i])
			|| buf[i] == '|' || buf[i] == '<' || buf[i] == '>'))
			break ;
		i++;
	}
	return (i);
}

char *extract_word(char *buf)
{
	int i;
	int size;
	char *line;

	size = extract_size(buf);
	i = 0;
	if (!buf)
		return (NULL);
	line = malloc(size + 1);
	if (!line)
		return (NULL);
	while (buf[i] && i < size)
	{
		line[i] = buf[i];
		i++;
	}
	return (line[i] = 0, line);
}
