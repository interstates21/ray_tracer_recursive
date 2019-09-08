#******************************************************************************#
#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okupin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/02 01:43:55 by okupin            #+#    #+#              #
#    Updated: 2018/02/02 01:44:05 by okupin           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = rtv1
PATH_SRC = ./
PATH_OBJ = ./
PATH_INC = ./libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEAD = rtv1.h

SRC =	main.c \
		mlx.c \
		controls.c \
		raytrace.c \
		raytrace2.c \
		vector1.c \
		list.c \
		vector2.c\
		scene_constructor.c \
		scene_constructor2.c \
		coloring_other.c \
		linear.c \
		scenes.c \
		intersections.c \
		coloring.c \
		color_math.c

OBJ = $(patsubst %.c,%.o,$(addprefix $(PATH_SRC), $(SRC)))


all: $(NAME)

$(NAME): $(OBJ) $(HEAD)
	make -C libft/
	$(CC) $(CFLAGS) -I $(PATH_INC) -c $(SRC)
	$(CC) -o $(NAME) $(OBJ) -lm -L libft/ -lft -L MinilibX/ -lmlx -framework OpenGL -framework AppKit

clean:
	make -C libft/ clean
	/bin/rm -rf *.o
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all re @(NAME)