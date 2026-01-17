#include "../../src/minishell.h"

int	tab_len(char **tab)
{
	int i = 0;
	while (tab && tab[i])
		i++;
	return i;
}

char	*make_pair(char *key, char *value)
{
	char *tmp;
	char *res;

	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return res;
}

void	free_tab(char **tab)
{
	int i = 0;

	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}
