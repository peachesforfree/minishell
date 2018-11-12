NAME = mini_shell

CC = gcc

FLAGS = -Wall -Werror -Wextra

BUGGER = -fsanitize=address

FILES = take3.c

LIBS = libft/libft.a

INCLUDE = -I.

OBJS = $(SRCS:.c=.o)

all: $(NAME)

debug:
	make -C libft	
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) $(LIBS) -o $(NAME) $(BUGGER)

$(NAME):
	make -C libft
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) $(LIBS) -o $(NAME)



fclean:
	$(RM) $(NAME)
	make -C libft fclean

clean: fclean
	make -C libft clean

re: fclean all%