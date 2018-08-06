# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/08/06 12:26:23 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fast_trig \
mat_copy mat_mult \
mat_set_identity mat_set_row \
mat_translate mat_scale mat_rotate \
mat_look_at mat_inverse \
p3d_math p3d_transform p3d_project

NAME=lib3d.a
INCLUDES=lib3d.h
HEADERS=$(INCLUDES:%=includes/%)
OBJS=$(SRCS:=.o)
CFLAGS=-Wall -Wextra -Werror -Wconversion -Ofast

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $?

$(OBJS): %.o:srcs/%.c $(HEADERS)
	gcc $(CFLAGS) -I includes -c $(@:%.o=srcs/%.c)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
