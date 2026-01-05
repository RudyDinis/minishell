/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:39:23 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/07 08:43:29 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char const *s, char *c)
{
	size_t	word_count;
	int		i;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		if (s[i] && !is_sep(s[i], c))
			word_count++;
		while (s[i] && !is_sep(s[i], c))
			i++;
	}
	return (word_count);
}

static char	*copy(const char *s, char *c)
{
	size_t	letter;
	int		i;
	char	*copy;

	letter = 0;
	i = 0;
	while (s[letter] && !is_sep(s[letter], c))
		letter++;
	copy = malloc(letter + 1);
	if (!copy)
		return (NULL);
	while (s[i] && !is_sep(s[i], c))
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	**ft_split(char const *s, char *c)
{
	size_t	word_count;
	size_t	actual_word;
	int		i;
	char	**split;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	actual_word = 0;
	i = 0;
	split = malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i] && actual_word < word_count)
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		split[actual_word] = copy(&s[i], c);
		if (!split[actual_word])
			return (free_everything((void **)split), NULL);
		actual_word++;
		while (s[i] && !is_sep(s[i], c))
			i++;
	}
	return (split[actual_word] = NULL, split);
}
