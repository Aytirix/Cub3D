# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 14:50:05 by hle-roux          #+#    #+#              #
#    Updated: 2024/09/03 18:52:28 by hle-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -I/usr/include -Imlx
LFLAGS = -L ft_printf/ -lftprintf -lreadline -Lmlx -lmlx_Linux
X11_FLAGS = -L/usr/X11/lib -lXext -lX11


NAME = cub3d

SRC = 	main.c \
		get_map.c \
		utils.c \
		window.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		init.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C ft_printf/
	$(CC) -o $@ $^ -Lmlx -lmlx -Lft_printf -lftprintf -Ift_printf $(X11_FLAGS) -lm

%.o : %.c
	$(CC) -Wall -Wextra -o $@ -c $<

clean:
	@$(MAKE) -C ft_printf/ clean
	rm -rf *.o
	rm -rf gnl/*.o

fclean: clean
	@$(MAKE) -C ft_printf/ fclean
	rm -f $(NAME)

re: fclean all
