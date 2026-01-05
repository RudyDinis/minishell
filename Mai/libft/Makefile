NAME = libft.a
NAME_BONUS = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs
RM = rm -f

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
      ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
      ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      ft_atoi.c ft_calloc.c ft_strdup.c \
      ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
      ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
      ft_putendl_fd.c ft_putnbr_fd.c ft_lstadd_back.c  ft_lstadd_front.c \
	  ft_lstlast.c ft_findstr.c free_char.c free_int.c \
	  ft_lstnew.c  ft_lstsize.c hexa_conversion.c \
	  ft_printf/ft_printf.c ft_printf/srcs/hexa_conversion.c ft_printf/srcs/check_type.c ft_printf/srcs/ft_put_counter.c \
	  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	  ft_printf_error/ft_printf_error.c ft_printf_error/srcs/hexa_conversion.c ft_printf_error/srcs/check_type.c ft_printf_error/srcs/ft_put_counter.c

OBJ = $(SRC:.c=.o)

HEADER = libft.h ft_printf/includes/ft_printf.h get_next_line/get_next_line.h ft_printf_error/includes/ft_printf_error.h

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	make -C ft_printf clean
	make -C ft_printf_error clean
	make -C get_next_line clean

fclean: clean
	@$(RM) $(NAME) $(NAME)
	make -C ft_printf fclean
	make -C ft_printf_error clean
	make -C get_next_line fclean

re: fclean all

.PHONY: all bonus clean fclean re
