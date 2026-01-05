NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC = main.c init_struct.c
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
