NAME = philo

SRCS =	philo.c \
		philo_utils.c\
		threads.c\


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g3

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf ./libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -rf libft/libft.a
	
re: fclean all
