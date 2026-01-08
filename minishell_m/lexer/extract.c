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

char *extract_word(char *buf)
{
	int i;
	char *line;

	i = 0;
	if (!buf)
		return (NULL);
	// if (*buf == '\"')
	// 	return extract_word_dquotes(buf);
	// if (*buf == '\'')
	// 	return extract_word_squotes(buf);
	while (buf[i] && buf[i] != ' ')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = 0;
	i = 0;
	while (buf[i] && buf[i] != ' ')
	{
		line[i] = buf[i];
		i++;
	}
	return line;
}
