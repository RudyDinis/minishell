NAME = minishell

SRCS = src/main.c src/signal.c
OBJS = $(SRCS:.c=.o)

LIBFT = utils/libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -I .
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(OBJS) $(LIBFT)/libft.a $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all
