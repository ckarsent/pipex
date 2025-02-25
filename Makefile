NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -g3
LIBFT_DOSS = Libft
LIBFT = $(LIBFT_DOSS)/libft.a

SRCS = pipex.c cmd.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DOSS)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DOSS) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DOSS) fclean

re: fclean all

.PHONY: all clean fclean re
