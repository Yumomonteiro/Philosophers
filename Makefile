NAME    = philo
CC      = cc -g
CFLAGS  = -Wall -Wextra -Werror -g -fsanitize=thread

SRCS    = main.c \
			srcs/ft_atoi.c srcs/philo.c srcs/routine.c srcs/time.c srcs/utils.c

OBJS    = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	make clean

fclean: clean
	$(RM) $(NAME)
	make fclean

re: fclean all

.PHONY: all clean fclean re

.SILENT:
