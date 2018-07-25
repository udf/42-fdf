# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/07/25 22:15:46 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=main.c util.c hook_key.c hook_mouse.c draw.c
NAME=fdf
CFLAGS=-Wall -Wextra -Werror -Wconversion
INCLUDES=-I libft/includes -I lib3d/includes
LIBS=-L libft/ -L lib3d/ -lft -l3d -lX11 -lmlx -lXext

all: $(NAME)

$(NAME): $(SRCS)
	make -C libft
	make -C lib3d
	gcc $(CFLAGS) $(INCLUDES) $(SRCS) -o $(NAME) $(LIBS)

clean:
	@echo ""

fclean: clean
	rm -f $(NAME)

re: fclean all
