/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:34:41 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 12:42:44 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*write_line(void)
{
	char		*prompt;
	size_t		prompt_len;
	char		*top;
	char		*bottom;
	char		*pwd;

	pwd = getcwd(NULL, 0);

	top = GREEN "┌──(" BOLD_BLUE "Minishell" RESET GREEN ")-[" BOLD_WHITE;
	bottom = RESET GREEN "]\n" GREEN "└─" BOLD_BLUE "$ " RESET;
	prompt_len = strlen(top)
		+ strlen(pwd)
		+ strlen(bottom)
		+ 1;
	prompt = malloc(prompt_len);
	if (!prompt)
		return (exit(1), NULL);
	ft_strcpy(prompt, top);
	ft_strcat(prompt, pwd);
	ft_strcat(prompt, bottom);
	free(pwd);
	return (prompt);
}

void	print_title(void)
{
	printf("\033[H\033[J");
	printf(
		BLUE
		"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
		"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
		"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"
		"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
		"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\n\n"
		RESET
		);
}
