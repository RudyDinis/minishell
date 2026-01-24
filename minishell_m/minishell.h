/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/24 18:13:39 by bbouarab         ###   ########.fr       */
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

# include "minishell_struct.h"

extern int	g_stop;

/*STRUCTURE INITIALISATION*/
t_cmd		*init_cmd(t_minishell *minishell, t_token *token);
t_token		*create_list(char *buf);
t_repere	init_repere(void);
t_opcounter	init_counter(void);
t_minishell	*init_ms(char **envp);

/*MAIN*/
void		print_title(void);
void		write_line(void);

/*EXEC*/
int			**malloc_fds(int total_args, t_cmd *cmd);
void		tree_of_closing(int **fds, int current_process, int total_args);
void		here_doc(t_cmd *cmd, char *lim, int i);
void		malloc_redir(t_cmd *cmd);
void		open_pipes(int **fds, int total_args);
void		close_all_pipes(int **fds, int total_args);
void		open_redir(t_cmd *cmd, int **fds);
void		apply_path(t_cmd *cmd);
void		launcher(t_cmd *cmd);

/*FREE UTILS*/
void		free_ms(t_token *token, t_cmd *cmd, int n);
void		free_cmd(t_cmd *cmd, int n);
void		free_token(t_token *token, int n);
void		free_minishell(t_minishell *data);

/*LEXER UTILS*/
int			is_blank(char c);
int			check_quotes_error(int token, t_repere repere);
int			assign_type(char *c, t_token *token, t_repere *repere);
char		*extract_word(char *buf);
void		if_space(t_repere *repere);
void		if_s_quotes(t_repere *repere);
void		if_d_quotes(t_repere *repere);
void		find_type(char *buf, t_token *token);

/*PARSER UTILS*/
int			check_formatting(t_token *token, t_minishell *minishell);
void		append_args(t_cmd *cmd, t_token *token);

/*GENERAL UTILS*/
int			number_of_cmds(t_token *token);
int			get_total_cmds(t_cmd *cmd);
int			find_number_of_token(char *buf);
int			get_here_doc_nbr(t_token *token);
char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dest, char *src);

/*EXPANDER*/
int			check_null_in_quotes(char *s);
void		expander(t_cmd *cmd);
void		get_here_doc_expand(t_token *token, t_cmd *cmd);
void		here_doc_expand(t_cmd *cmd, char *lim, int i);
void		free_tab(char **tab);
void		debug_print(const char *s);
char		*ignore_quotes(char *str);
char		**expand_vars(char *s, t_minishell *data, char *param);
char		*get_env_value(char *name, t_minishell *data);
char		*get_var_value(char *name, t_minishell *data);
char		*expand_one_var_doc(t_expand_vars_vars *vars,
				t_minishell *data, int quoted);
char		**expand_vars_doc(char *s, t_minishell *data, char *param);
char		*char_join(char *s, char c);
char		**expand_vars_jsp(char *s, t_minishell *data, char *param);
char		*expand_one_var(t_expand_vars_vars *vars, t_minishell *data,
				int quoted);
char		*ft_strjoin_free(char *s1, char *s2);
char		*strdup_and_free(char *line, t_minishell *minishell, char *param);

/*BUILT-IN*/
int			export(char **argv, t_env *env);
void		echo(char **argv);
void		pwd(void);
void		cd(char **argv, t_minishell *data);
void		unset(t_minishell *data, char *key);
void		env(t_minishell *data);
void		exit_shell(t_cmd *cmd, char **argv);

/*SIGNALS*/
void		init_signals(void);
void		sigint_handler(int sig);
void		init_signals_parent_exec(void);
void		init_signals_child(void);

/*ENV*/
void		add_env(t_env **env, char *line);
void		add_var(t_var **var, char *key, char *value);
void		print_env(t_env *env);
t_env		*copy_env(char **envp);

#endif
