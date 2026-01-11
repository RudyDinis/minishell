NAME = minishell

SRCS = src/main.c src/signal.c
COMMANDSSRCS = src/commands/echo.c src/commands/export.c

OBJS = $(SRCS:.c=.o)
COMMANDSOBJS = $(COMMANDSSRCS:.c=.o)
LIBFT = utils/libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -I .
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) ${COMMANDSOBJS} $(LIBFT)/libft.a
	$(CC) $(OBJS) ${COMMANDSOBJS} $(LIBFT)/libft.a $(LDFLAGS) -o $(NAME)

$(LIBFT)/libft.a:
	make -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS) ${COMMANDSOBJS}

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all
