NAME = philo

SRCS =	philo.c \
		philo_utils.c\
		threads.c\


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@make -C ./printf
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf ./libft/*.o
	rm -rf ./printf/*.o

fclean: clean
	rm -f $(NAME)
	rm -rf libft/libft.a
	rm -rf printf/libftprintf.a

re: fclean all
