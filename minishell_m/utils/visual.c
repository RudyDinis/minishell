/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:34:41 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/21 15:47:07 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    write_line(void)
{
    char        *prompt;
    size_t        prompt_len;
    char        *top;
    char        *bottom;
    char        *pwd;

    pwd = getcwd(NULL, 0);

    top = GREEN "┌──(" BOLD_BLUE "Minishell" RESET GREEN ")-[" BOLD_WHITE;
    bottom = RESET GREEN "]\n";
    prompt_len = ft_strlen(top)
        + ft_strlen(pwd)
        + ft_strlen(bottom)
        + 1;
    prompt = malloc(prompt_len);
    if (!prompt)
        return (exit(1));
    ft_strcpy(prompt, top);
    ft_strcat(prompt, pwd);
    ft_strcat(prompt, bottom);
    free(pwd);
    printf("%s", prompt);
    free(prompt);
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
