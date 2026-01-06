NAME = libgnl.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./
AR = ar rcs
RM = rm -f

SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
HEADER = get_next_line.h

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
