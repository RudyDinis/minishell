NAME = minishell
CC = gcc
CFLAGS = -g
AR = ar rcs
RM = rm -f

SRC = main.c init_struct.c free_ms.c \
		lexer/find_and_assign_type.c lexer/find_token_nbr.c lexer/find_token_nbr_utils.c lexer/extract.c \
		parser/formatting_and_redir.c parser/add_commands.c \
		exec/exec.c exec/closing_processes.c exec/exec_redir.c exec/exec_utils.c exec/find_path.c exec/here_doc.c \
		expand/expander.c expand/expand_utils.c expand/expand_utils2.c

OBJ = $(SRC:.c=.o)
HEADER = minishell.h minishell_struct.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ)  -lreadline -L./libft -lft -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
