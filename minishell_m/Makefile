NAME = minishell
CC = gcc
CFLAGS = -g
AR = ar rcs
RM = rm -rf
OBJ_DIR = obj

SRC = main.c \
		utils/init_struct.c utils/free_ms.c utils/visual.c utils/signal.c \
		lexer/find_and_assign_type.c lexer/find_token_nbr.c lexer/find_token_nbr_utils.c lexer/extract.c \
		parser/formatting_and_redir.c parser/add_commands.c \
		exec/exec.c exec/closing_processes.c exec/exec_redir.c exec/exec_utils.c exec/find_path.c exec/here_doc.c \
		expand/expander.c expand/expand_utils.c expand/expand_utils2.c \
		built-in/cd.c built-in/echo.c built-in/env.c built-in/export.c built-in/exit.c built-in/unset.c built-in/pwd.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
HEADER = minishell.h minishell_struct.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ)  -lreadline -L./libft -lft -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./libft clean
	$(RM) $(OBJ_DIR)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
