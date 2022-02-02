NAME		=	libftprintf.a

SRCS		=	ft_printf.c \
				get_args.c \
				print_int.c \
				print_char.c \
				utils_char.c \
				print_hexa.c \
				print_octal.c \
				print_float.c \
				utils_float.c \
				utils.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			ar rc $@ $^

all:		$(NAME)

bonus:		all

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
