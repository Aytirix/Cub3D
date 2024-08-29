# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hle-roux <hle-roux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 20:29:29 by hle-roux          #+#    #+#              #
#    Updated: 2024/08/29 16:56:57 by hle-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl

SRC =	get_next_line.c \
		get_next_line_utils.c \

OBJ = ${SRC:.c=.o}

HEADER = .

all : $(NAME)

$(NAME) : $(OBJ)
	gcc -fPIE -Wall -Werror -Wextra -o $@ $<

clean :
	/bin/rm -f ${OBJ}

fclean : clean

re : fclean all
