# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/08/06 12:28:43 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=main.c input.c colour_map.c util.c util_ipoint.c util_colour.c hook_key.c \
hook_mouse.c image_draw.c loop.c draw.c
NAME=fdf
CFLAGS=-Wall -Wextra -Werror -Wconversion -O3
INCLUDES=-I libft/includes -I lib3d/includes
UNAME_S := $(shell uname -s)
LIBS=-L libft/ -L lib3d/ -lm -lft -l3d -lmlx
ifeq ($(UNAME_S),Linux)
	LIBS += -lXext -lX11
endif
ifeq ($(UNAME_S),Darwin)
	LIBS +=	-framework OpenGL -framework AppKit
endif

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
