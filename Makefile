NAME = mini_shell

CC = gcc

FLAGS = -Wall -Werror -Wextra

FILES = take3.c

LIBS = libft/libft.a

INCLUDE = -I.

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	
$(NAME):
	make -C libft
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) $(LIBS)

fclean:
	$(RM) $(NAME)
	make -C libft fclean

clean: fclean
	make -C libft clean

re: fclean all%