# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/07/24 15:24:22 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=main.c util.c hook_key.c hook_mouse.c hook_expose.c hook_loop.c
NAME=fdf
CFLAGS=-Wall -Wextra -Werror -Wconversion
INCLUDES=-I libft/includes
LIBS=-L libft/ -lft -lX11 -lmlx -lXext

all: $(NAME)

$(NAME): $(SRCS)
	make -C libft
	gcc $(CFLAGS) $(INCLUDES) $(SRCS) -o $(NAME) $(LIBS)

clean:
	@echo ""

fclean: clean
	rm -f $(NAME)

re: fclean all
