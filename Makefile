# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/08/02 16:01:41 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=main.c input.c colour_map.c util.c util_ipoint.c hook_key.c \
hook_mouse.c image_draw.c loop.c draw.c
NAME=fdf
CFLAGS=-Wall -Wextra -Werror -Wconversion -O3
INCLUDES=-I libft/includes -I lib3d/includes
LIBS=-L libft/ -L lib3d/ -lft -l3d -lm -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(SRCS)
	make -C libft
	make -C lib3d
	gcc $(CFLAGS) $(INCLUDES) $(SRCS) -o $(NAME) $(LIBS)

clean:
	@echo "No objects to clean"

fclean: clean
	rm -f $(NAME)

re: fclean all
