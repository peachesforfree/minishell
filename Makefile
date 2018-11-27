NAME = mini_shell

CC = gcc

FLAGS = -Wall -Werror -Wextra

BUGGER = -fsanitize=address

FILES = sources/main.c \
		sources/unsetenv.c \
		sources/string_manip2.c \
		sources/string_manip.c \
		sources/start_func.c \
		sources/setenv.c \
		sources/misc_util.c \
		sources/misc_builtin.c \
		sources/list_func2.c \
		sources/list_func.c \
		sources/fork_exec.c \
		sources/env_expansion.c \
		sources/end_func.c \
		sources/echo.c \
		sources/dir_read.c \
		sources/command_parse.c \
		sources/cd.c \
		sources/free.c

LIBS = libft/libft.a

INCLUDE = -I.

OBJS = $(SRCS:.c=.o)

all: $(NAME)

debug:
	make -C libft	
	$(CC) -g $(FLAGS) $(FILES) $(INCLUDE) $(LIBS) -o $(NAME)

$(NAME):
	make -C libft
	$(CC) $(FLAGS) $(FILES) $(INCLUDE) $(LIBS) -o $(NAME)



fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

clean:
	make -C libft clean

re: fclean all