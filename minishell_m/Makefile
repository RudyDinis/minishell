NAME = minishell
CC = gcc
CFLAGS = -g
AR = ar rcs
RM = rm -f

SRC = main.c init_struct.c lexer/find_and_assign_type.c \
		lexer/find_token_nbr.c lexer/find_token_nbr_utils.c lexer/extract.c \
		parser/check_formatting.c
OBJ = $(SRC:.c=.o)
HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ)  -L./libft -lft -o $@

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
