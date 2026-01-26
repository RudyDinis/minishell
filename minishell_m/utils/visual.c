/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:34:41 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/26 15:40:52 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_line(t_minishell *minishell)
{
	char	*prompt;
	char	*top;
	char	*bottom;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = ft_strdup(get_env_value("PWD", minishell));
		minishell->pwd_err = 1;
	}
	top = GREEN "┌──(" BOLD_BLUE "Minishell" RESET GREEN ")-[" BOLD_WHITE;
	bottom = RESET GREEN "]\n";
	prompt = malloc(ft_strlen(top) + ft_strlen(pwd) + ft_strlen(bottom) + 1);
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
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		RESET);
}
