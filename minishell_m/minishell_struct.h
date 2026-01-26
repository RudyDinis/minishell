/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/18 13:37:42 by kube              #+#    #+#             */
/*   Updated: 2026/01/26 15:21:28 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef enum s_type
{
	STR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC
}	t_type;

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
	int				last_cmd_return_value;
	int				in_here_doc;
	char			*gnl;
	int				pwd_err;
	char			*line;
	char			**envp;
	t_env			*env;
	t_var			*var;
	struct s_cmd	*cmd;
}	t_minishell;

typedef struct s_token
{
	int				in_quotes;
	int				index;
	char			*line;
	t_type			type;
	struct s_token	*next;
	struct s_token	*previous;
	struct s_cmd	*cmd;
}	t_token;

typedef struct s_repere
{
	bool	in_s_quote;
	bool	in_d_quote;
	bool	in_word;
	bool	in_pipe;
	bool	in_redir_in;
	bool	in_redir_out;
	bool	error;
}	t_repere;

typedef struct s_opcounter
{
	int	pipe;
	int	redir_out;
	int	redir_in;
}	t_opcounter;

typedef struct s_redir
{
	long	redir_number;
	int		*fd;
	int		*here_doc_expand;
	char	**target;
	t_type	*redir_type;
}	t_redir;

typedef struct s_cmd
{
	int				return_value;
	int				**fds;
	long			i;
	bool			expanded;
	bool			cmd_found;
	bool			is_absolute;
	pid_t			pid;
	char			*cmd;
	char			*path;
	char			**args;
	t_redir			*redir;
	t_token			*token;
	t_minishell		*minishell;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_expand_vars_vars
{
	int		i;
	int		a;
	int		in_quotes;
	char	*s;
	char	*res;
}	t_expand_vars_vars;

#endif
