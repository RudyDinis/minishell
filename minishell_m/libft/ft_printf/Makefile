NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/
AR = ar rcs
RM = rm -f

SRC = ft_printf.c srcs/hexa_conversion.c srcs/check_type.c srcs/ft_put_counter.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
