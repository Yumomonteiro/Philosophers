NAME    = philo
CC      = cc -g
CFLAGS  = -Wall -Wextra -Werror -g #-fsanitize=thread

SRCS    = main.c \
			srcs/init.c srcs/monitor.c srcs/routine.c srcs/time.c srcs/print_action.c

OBJS    = $(SRCS:.c=.o)

LIBFT   = libs/libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C libs/libft -s

clean:
	$(RM) $(OBJS)
	make clean -C libs/libft -s

fclean: clean
	$(RM) $(NAME)
	make fclean -C libs/libft -s

re: fclean all

.PHONY: all clean fclean re

.SILENT:
