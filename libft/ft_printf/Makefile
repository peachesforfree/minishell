# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/31 11:42:23 by sbalcort          #+#    #+#              #
#    Updated: 2018/07/05 19:00:42 by sbalcort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

FLAGS = -Wall -Werror -Wextra -I. -c

HEADER = ft_printf.h

SRCS = ft_printf.c \
	   ft_isdigit.c \
	   ft_putchar.c \
	   ft_atoi.c \
	   ft_strlen.c \
	   ft_put_mem.c \
	   put_numbers.c \
	   put_strings.c \
	   type_casting.c \
	   misc_printing.c \
	   flag_checking.c \
	   ft_isspace.c

OBJS = $(SRCS:.c=.o)

$(NAME):
	$(CC) $(FLAGS) $(SRCS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)
	
test:
	gcc -g derps.c $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
re:fclean all
