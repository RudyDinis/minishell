#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>

typedef enum s_type
{
	STR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC
}	t_type;

typedef struct s_token
{
	char	*line;
	int		in_quotes;
	int		index;
	t_type	type;
	struct s_token *next;
	struct s_token *previous;
	struct s_cmd	*cmd;
}	t_token;

typedef struct s_repere
{
	int in_s_quote;
	int in_d_quote;
	int in_word;
	int in_pipe;
	int in_redir_in;
	int in_redir_out;
} t_repere;

typedef struct s_opcounter
{
	int pipe;
	int redir_out;
	int redir_in;
}	t_opcounter;

typedef struct s_redir
{
	t_type	*redir_type;
	char	**target;
	int 	*fd;
	int		redir_number;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	char 			*cmd;
	char 			*path;
	t_redir			*redir;
	struct s_cmd	*next;
	int				i;
	int				is_absolute;
	pid_t			pid;
	int				return_value;
	t_token			*token;
	struct s_minishell	*minishell;
}	t_cmd;

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

typedef struct s_minishell
{
	char	*pwd;
	t_env	*env;
	t_var	*var;
	int last_cmd_return_value;
}	t_minishell;

void	tree_of_closing(int **fds, int current_process, int total_args);
void if_space(t_repere *repere);
void if_s_quotes(t_repere *repere);
void if_d_quotes(t_repere *repere);
int check_quotes_error(int token, t_repere repere);
void append_args(t_cmd *cmd, t_token *token);
void launcher(t_cmd *cmd, t_token *token);
int is_blank(char c);
void find_type(char *buf, t_token *token);
char *extract_word(char *buf);
t_token *create_list(char *buf);
int find_number_of_token(char *buf);
int assign_type(char *c, t_token *token, t_repere *repere);
t_repere init_repere(void);
t_opcounter init_counter(void);
t_cmd *init_cmd(t_token *token);
int number_of_cmds(t_token *token);
void check_formatting(t_token *token);
void malloc_redir(t_cmd *cmd, int **fds);
int **malloc_fds(int total_args, t_cmd *cmd);
void open_pipes(int **fds, int total_args);
void close_all_pipes(int **fds, int total_args);
int get_total_cmds(t_cmd *cmd);
void open_redir(t_cmd *cmd, int **fds);
void apply_path(t_cmd *cmd);
char	**expand_vars(char *s, t_minishell *data);
void free_ms(t_token *token, t_cmd *cmd, int n, int **fds);
void free_cmd(t_cmd *cmd, int n);
void free_token(t_token *token, int n);
void expander(t_cmd *cmd);
char	*get_env_value(char *name, char *value, t_minishell *data);
char	*get_var_value(char *name, char *value, t_minishell *data);
#endif
