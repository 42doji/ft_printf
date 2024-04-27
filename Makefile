# **************************************************************************** #
# include <stdio.h>
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doji <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 21:25:20 by doji              #+#    #+#              #
#    Updated: 2024/04/25 22:33:58 by doji             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBRARY = libftprintf.a
NAME = ft_printf.c ft_printf_utils_i.c ft_printf_utils_ii.c ft_printf_utils_iii.c
OBJS = $(NAME:.c=.o)
WARN = -Wall -Werror -Wextra
CFLAGS = $(WARN) -g
CC = cc

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

clean:
	-rm -f $(OBJS)
re:
	make clean
	make all
fclean:
	make clean
	-rm -f $(LIBRARY)

.PHONY: clean re fclean all
