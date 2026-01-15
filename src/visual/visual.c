/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:34:41 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/14 16:13:21 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*write_line(t_minishell *data)
{
	char		*prompt;
	size_t		prompt_len;
	char		*top;
	char		*bottom;

	top = GREEN "\n┌──(" BOLD_BLUE "Minishell" RESET GREEN ")-[" BOLD_WHITE;
	bottom = RESET GREEN "]\n" GREEN "└─" BOLD_BLUE "$ " RESET;
	prompt_len = strlen(top)
		+ strlen(data->pwd)
		+ strlen(bottom)
		+ 1;
	prompt = malloc(prompt_len);
	if (!prompt)
		return (prompt);
	strcpy(prompt, top);//EDIT TO LIBFT
	strcat(prompt, data->pwd);//EDIT TO LIBFT
	strcat(prompt, bottom);//EDIT TO LIBFT
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
