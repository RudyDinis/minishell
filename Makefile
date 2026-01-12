NAME = minishell
CC = gcc
CFLAGS = -g
AR = ar rcs
RM = rm -f
SRC = src/main.c src/visual/visual.c src/signal/signal.c src/var/var.c
COMMANDSSRC = src/commands/echo.c src/commands/export.c src/commands/cd.c

OBJ = $(SRC:.c=.o)
COMMANDSOBJ = $(COMMANDSSRC:.c=.o)

HEADER = src/minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(COMMANDSOBJ) $(HEADER)
	make -C ./utils/libft
	$(CC) $(CFLAGS) $(OBJ) $(COMMANDSOBJ) -lreadline -L./utils/libft -lft -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./utils/libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C ./utils/libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re