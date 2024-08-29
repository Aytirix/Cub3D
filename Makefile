# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 14:50:05 by hle-roux          #+#    #+#              #
#    Updated: 2024/08/29 16:56:47 by hle-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC =	main.c \
		get_map.c \
		utils.c \
		#get_next_line.c \
		#get_next_line_utils.c \
		#parsing.c \
		#side_fonctions.c \
		#win_creation.c \
		#player_movement.c \
		#pathfinding.c \

CFLAGS =  -Wall -Wextra -Werror -Imlx -c

OBJ = ${SRC:.c=.o}

HEADER = .

all : $(NAME)

$(NAME) : $(OBJ)
	make -C ft_printf
	make -C gnl
	gcc -fPIE -Lft_printf -lftprintf $(OBJ) -o $(NAME)


ft_printf :
	make -C ft_printf

clean :
	/bin/rm -f ${OBJ}
	make -C ft_printf clean

fclean : clean
	rm -f cub3d ft_printf/libftprintf.a

re : fclean all
