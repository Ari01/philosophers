NAME	=	philo

SRCS	=	atoi.c \
			main.c \
			print.c \
			threads.c \
			utils.c \
			philo.c \
			actions.c \
			eat.c \
			list.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

debug:		$(OBJS)
			$(CC) $(CFLAGS) -g -fsanitize=address $(OBJS) -o $@
.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)
			rm -rf .*.swp

re:			fclean all

.PHONY:		all clean fclean re
