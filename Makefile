NAME = mini_shell

CC = gcc

FLAGS = -Wall -Werror -Wextra

BUGGER = -fsanitize=address

FILES = main.c \
		unsetenv.c \
		string_manip2.c \
		string_manip.c \
		start_func.c \
		setenv.c \
		misc_util.c \
		misc_builtin.c \
		list_func2.c \
		list_func.c \
		fork_exec.c \
		env_expansion.c \
		end_func.c \
		echo.c \
		dir_read.c \
		command_parse.c \
		cd.c

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



fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

clean:
	make -C libft clean

re: fclean all