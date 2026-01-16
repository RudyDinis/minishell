/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:49:11 by rdinis            #+#    #+#             */
/*   Updated: 2026/01/14 17:34:32 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define BOLD_RED	"\033[1;31m"
# define BOLD_GREEN	"\033[1;32m"
# define BOLD_BLUE	"\033[1;34m"
# define BOLD_WHITE	"\033[1;37m"
# define RESET		"\033[0m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../utils/libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_expand_vars_vars
{
	int		i;
	char	*res;
	int		in_quotes;
	char	*s;
}	t_expand_vars_vars;

typedef struct s_minishell
{
	char	*pwd;
	t_env	*env;
	t_var	*var;
	int		last_cmd_return_value;
	int		exit_status;
}	t_minishell;

void	init_signals(t_minishell *data);
void	sigint_handler(int sig);

void	add_env(t_env **env, char *line);
void	add_var(t_var **var, char *key, char *value);
void	print_env(t_env *env);

char	**expand_vars(char *s, t_minishell *data, char *param);
char	*get_env_value(char *name, char *value, t_minishell *data);
char	*get_var_value(char *name, char *value, t_minishell *data);
char	*expand_one_var(char *s, int *i, char *res, t_minishell *data);

void	cd(char **argv, t_minishell *data);
void	echo(char **argv);
int		export(char **argv, t_env *env);
void	exit_shell(t_minishell *data);

void	print_title(void);
char	*write_line(t_minishell *data);

#endif